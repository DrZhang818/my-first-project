#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

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

    vector<int> dp(n + 1);
    int ans = 0;

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        dp[u] = int(adj[u].size()) >= 2 ? 1 : 0;

        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            if(adj[u].size() >= 4) {
                if(adj[v].size() >= 4) {
                    ans = max(ans, dp[u] + dp[v]);
                    dp[u] = max(dp[u], dp[v] + 1);
                } else if(adj[v].size() == 3) {
                    ans = max(ans, dp[u] + 1);
                    dp[u] = max(dp[u], 2);
                }
            } else if(adj[u].size() == 3) {
                if(adj[v].size() >= 4) {
                    ans = max(ans, 1 + dp[v]);
                    dp[u] = max(dp[u], dp[v] + 1);
                } else if(adj[v].size() == 3) {
                    ans = max(ans, 2);
                    dp[u] = max(dp[u], 2);                    
                }
            }
        }

        ans = max(ans, dp[u]);
    };
    dfs(1, 0);

    cout << ans << "\n";    
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
