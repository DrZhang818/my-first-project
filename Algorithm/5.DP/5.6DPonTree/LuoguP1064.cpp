#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> m >> n;
    vector<vector<int>> adj(n + 1); 
    vector<int> c(n + 1), w(n + 1);
    for(int i = 1; i <= n; i++) {
        int fa;
        cin >> c[i] >> w[i] >> fa;
        w[i] *= c[i];
        if(fa) {
            adj[fa].push_back(i);
        } else {
            adj[0].push_back(i);
        }
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int u, int k) -> void {
        for(int v : adj[u]) {
            if(k < c[v]) continue;
            for(int i = 0; i <= k - c[v]; i++) {
                dp[v][i] = dp[u][i] + w[v];
            } 
            self(self, v, k - c[v]);
            for(int i = c[v]; i <= k; i++) {
                dp[u][i] = max(dp[u][i], dp[v][i - c[v]]);
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
