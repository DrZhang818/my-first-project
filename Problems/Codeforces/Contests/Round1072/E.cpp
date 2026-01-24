#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa, sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return ;
    fa[v] = u;
    sz[u] += sz[v];
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector adj(n + 1, vector<int>{});
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(i > 1) {
            adj[abs(a[i] - a[i - 1])].push_back(i - 1);
        }
    }
    fa.assign(n, 0);
    iota(fa.begin(), fa.end(), 0);
    sz.assign(n, 0);
    vector<ll> ans(n);
    ll cnt = 0;
    for(int d = n - 1; d >= 1; d--) {
        for(int u : adj[d]) {
            sz[u] = 1;
            if(u - 1 >= 1) {
                int x = find(u - 1);
                if(sz[x]) {
                    cnt -= 1LL * sz[x] * (sz[x] + 1) / 2;
                    merge(u, x);
                }
            }
            if(u + 1 <= n - 1) {
                int x = find(u + 1);
                if(sz[x]) {
                    cnt -= 1LL * sz[x] * (sz[x] + 1) / 2;
                    merge(u, x);
                }
            }
            int x = find(u);
            cnt += 1LL * sz[x] * (sz[x] + 1) / 2;
        }
        ans[d] = cnt;
    }
    for(int d = 1; d < n; d++) {
        cout << ans[d] << " \n"[d == n - 1];
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
