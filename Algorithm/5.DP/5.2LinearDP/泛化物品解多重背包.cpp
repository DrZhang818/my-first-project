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
    vector<int> c(n + 1), w(n + 1), sz(n + 1);
    for(int i = 1; i <= n; i++) {
        adj[0].push_back(i);
        cin >> c[i] >> w[i] >> sz[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int u, int k) -> void {
        for(int v : adj[u]) {
            for(int i = 0; i <= k - c[v]; i++) {
                dp[v][i] = dp[u][i] + w[v];
            }
            for(int i = 1; i <= k - c[v]; i++) {
                dp[v][i] = dp[v][i - 1]
            }
        }
    };  
    dfs(dfs, 0, m);
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
