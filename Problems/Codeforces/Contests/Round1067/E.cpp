#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int ans;
vector<int> fa, tag;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
    ans -= tag[u];
    ans -= tag[v];
    tag[u] &= tag[v];
    ans += tag[u];
}
void update(int o) {
    o = find(o);
    ans -= tag[o];
    tag[o] = 0;
}

int dir[5] = {-1, 0, 1, 0, -1};

void solve() {
    int n, m;
    cin >> n >> m;
    ans = n * m;
    vector a(n + 1, vector<int>(m + 1));
    vector idx(n + 1, vector<int>(m + 1));
    int sz = n * m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            idx[i][j] = (i - 1) * m + j;
        }
    }
    int q;
    cin >> q;
    fa.assign(n * m + q + 1, {});
    iota(fa.begin(), fa.end(), 0);
    tag.assign(n * m + q + 1, {1});
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int S = idx[i][j];
            for(int k = 0; k < 4; k++) {
                int x = i + dir[k];
                int y = j + dir[k + 1];
                if(x < 1 || x > n || y < 1 || y > m) {
                    continue;
                }
                int T = idx[x][y];
                if(a[i][j] == a[x][y]) {
                    merge(S, T);
                } else if(a[i][j] < a[x][y]) {
                    update(T);
                } else {
                    update(S);
                }
            }
        }
    }

    cout << ans << "\n";

    while(q--) {
        int i, j, x;
        cin >> i >> j >> x;
        update(idx[i][j]);
        a[i][j] -= x;
        idx[i][j] = ++sz;
        ans++;
        int S = idx[i][j];
        for(int k = 0; k < 4; k++) {
            int x = i + dir[k];
            int y = j + dir[k + 1];
            if(x < 1 || x > n || y < 1 || y > m) {
                continue;
            }
            int T = idx[x][y];
            if(a[i][j] == a[x][y]) {
                merge(S, T);
            } else if(a[i][j] < a[x][y]) {
                update(T);
            } else {
                update(S);
            }
        }
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
