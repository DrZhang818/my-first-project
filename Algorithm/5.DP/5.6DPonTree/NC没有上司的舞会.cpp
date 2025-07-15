#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/28258/B
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<int,2>> dp(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dp[u][1] = w[u];
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    };
    dfs(dfs, 1, 0);
    cout << max(dp[1][0], dp[1][1]) << "\n";
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
