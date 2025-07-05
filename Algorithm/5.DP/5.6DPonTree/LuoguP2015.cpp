#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int u, int fa, int k) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            for(int i = 0; i < k; i++) {
                dp[v][i] = dp[u][i] + w;
            }
            self(self, v, u, k - 1);
            for(int i = 1; i <= k; i++) {
                dp[u][i] = max(dp[u][i], dp[v][i - 1]);
            }
        }
    };
    dfs(dfs, 1, 0, m);
    cout << dp[1][m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
