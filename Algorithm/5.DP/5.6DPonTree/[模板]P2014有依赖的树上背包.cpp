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
    vector<int> w(n + 1);
    vector<vector<int>> adj(n + 1);
    vector<bool> rt(n + 1, true);
    for(int i = 1; i <= n; i++) {
        int u;
        cin >> u >> w[i];
        if(u) {
            adj[u].push_back(i);
            rt[i] = false;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(rt[i]) {
            adj[0].push_back(i);
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int u, int k) -> void {
        for(int v : adj[u]) {
            for(int i = 0; i < k; i++) {
                dp[v][i] = dp[u][i] + w[v];
            }
            self(self, v, k - 1);
            for(int i = 1; i <= k; i++) {
                dp[u][i] = max(dp[u][i], dp[v][i - 1]);
            }
        }
    };  
    dfs(dfs, 0, m);
    cout << dp[0][m] << "\n";
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
