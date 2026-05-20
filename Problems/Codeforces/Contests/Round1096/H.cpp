#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr i64 inf = 1E18;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    int rt = 1;
    while(deg[rt] == 1) rt++;

    vector<int> sz(n + 1);
    vector<i64> f(n + 1), g(n + 1);

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = deg[u] == 1 ? 1 : 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
            if(sz[v] % 2 == 0) {
                f[u] += f[v];
            } else {
                f[u] += f[v] + 1;
            }
        }

        i64 x = deg[u] == 1 ? 0 : inf;
        i64 y = deg[u] == 1 ? 0 : inf;
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(sz[v] & 1) {
                x = min(x, f[u] - f[v] - 1 + g[v]);
            } else {
                y = min(y, f[u] - f[v] + g[v] + 1);
            }
        }

        g[u] = min(x, y);
    };
    dfs(rt, 0);

    i64 ans = sz[rt] % 2 == 0 ? f[rt] : g[rt];
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}