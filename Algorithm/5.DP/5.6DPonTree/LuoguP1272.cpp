#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, inf));
    vector<int> sz(n + 1, 1);
    auto dfs = [&](auto &&self, int u) -> void {
        for(int v : adj[u]) {
            self(self, v);
            sz[u] += sz[v];
        }
        dp[u][0] = 0;
        dp[u][sz[u]] = 1;
        for(int v : adj[u]) {
            for(int i = sz[u] - 1; i >= 0; i--) {
                for(int j = 0; j <= i && j <= sz[v]; j++) {
                    dp[u][i] = min(dp[u][i], dp[u][i - j] + dp[v][j]);
                } 
            }
        }
    };
    dfs(dfs, 1);
    int ans = inf;
    for(int i = 1; i <= n; i++) {
        if(sz[i] >= m) {
            ans = min(ans, dp[i][sz[i] - m] + (i != 1));
        } 
    }
    cout << ans << "\n";
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
