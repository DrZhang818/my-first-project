#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<int, 20>> dp(n + 1);
    vector<int> sz(n + 1);
    vector<int> fa(n + 1);
    vector<int> top(n + 1);
    vector<int> dep(n + 1);

    auto dfs = [&](auto&& self, int u) -> void {
        if(fa[u]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        }
        sz[u] = 1;
        dp[u][a[u]]++;

        for(int& v : adj[u]) {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            for(int c = 0; c < 20; c++) {
                dp[v][c] = dp[u][c];
            }
            self(self, v);
            sz[u] += sz[v];
            if(sz[v] > sz[adj[u][0]]) {
                swap(adj[u][0], v);
            }
        }
    };
    dfs(dfs, 1);

    top[1] = 1;
    auto dfs2 = [&](auto&& self, int u) -> void {
        for(auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            self(self, v);
        }
    };
    dfs2(dfs2, 1);

    auto LCA = [&](int u, int v) -> int {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        if(dep[u] < dep[v]) swap(u, v);
        return v;
    };

    while(q--) {
        int u, v;
        cin >> u >> v;
        int lca = LCA(u, v);
        int res = 0;
        for(int c = 0; c < 20; c++) {
            res += (dp[u][c] + dp[v][c] - 2 * dp[lca][c] + (a[lca] == c) > 0 ? 1 : 0);
        }
        cout << res << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}