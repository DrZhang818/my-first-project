#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
vector<int> cnt;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return false;
    fa[v] = u;
    cnt[u] += cnt[v];
    return true;
}

void solve() {  
    int n, m, x, d;
    cin >> n >> m >> x >> d;
    vector<int> h(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    vector<PII> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[i] = {u, v};
    }

    vector<int> H(x + 1);
    for(int i = 1; i <= x; i++) {
        cin >> H[i];
    }

    fa.resize(n + 1);
    cnt.assign(n + 1, 1);
    iota(fa.begin(), fa.end(), 0);

    sort(e.begin() + 1, e.end(), 
        [&](auto a, auto b) {
            int t1 = min(h[a.first], h[a.second]);
            int t2 = min(h[b.first], h[b.second]);
            return t1 > t2;
        });

    vector<int> ans(x + 1);

    vector<int> p;
    if(d == 1) {
        p.resize(n + 1);
        iota(p.begin(), p.end(), 0);
        sort(p.begin() + 1, p.end(), 
            [&](auto x, auto y) {
                return h[x] > h[y];
            });
    }

    int cur = 0;
    int j = 1, k = 1;
    for(int i = x; i >= 1; i--) {
        if(d == 1) {
            while(k <= n && h[p[k]] > H[i]) {
                if(cnt[find(p[k])] == 1) {
                    cur++;
                }
                k++;
            }
        }

        while(j <= m && min(h[e[j].first], h[e[j].second]) > H[i]) {
            auto [u, v] = e[j];
            j++;    
            if(find(u) == find(v)) {
                continue;
            }
            if(cnt[find(u)] >= d) cur--;
            if(cnt[find(v)] >= d) cur--;
            merge(u, v);
            if(cnt[find(u)] >= d) cur++;
        }

        ans[i] = cur;
    }

    for(int i = 1; i <= x; i++) {
        cout << ans[i] << "\n";
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
