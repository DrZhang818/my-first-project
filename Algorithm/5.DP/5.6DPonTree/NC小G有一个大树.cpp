#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n + 1, 1), dp(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            dp[u] = max(dp[u], sz[v]);
        }
        dp[u] = max(dp[u], n - sz[u]);
    };
    dfs(dfs, 1, 0);
    int id = 0, mn = inf;
    for(int i = 1; i <= n; i++) {
        if(dp[i] < mn) {
            mn = dp[i];
            id = i;
        }
    }
    cout << id << " " << mn << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
