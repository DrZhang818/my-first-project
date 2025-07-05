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
    vector<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<ll,2>> dp(n + 1);
    auto dfs = [&](this auto &&self, int u, int f) -> void {
        dp[u][1] = max(0LL, dp[f][0]) + w[u];
        dp[u][0] = max(0LL, dp[f][1]) - w[u];
        for(int v : adj[u]) {
            if(v != f) {
                self(v, u);
            }
        }
    };
    dfs(1, 0);
    for(int i = 1; i <= n; i++) {
        cout << dp[i][1] << " \n"[i == n];
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
