#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/28258/D
//https://www.luogu.com.cn/problem/P2899
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
    vector<array<int,3>> dp(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dp[u][0] = 1;
        int mn = inf;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            dp[u][0] += min({dp[v][0], dp[v][1], dp[v][2]});
            dp[u][1] += min(dp[v][0], dp[v][2]);
            dp[u][2] += min(dp[v][0], dp[v][2]);
            mn = min(mn, dp[v][0] - dp[v][2]);
        }
        if(mn > 0) dp[u][2] += mn;
    };
    dfs(dfs, 1, 0);
    cout << min(dp[1][0], dp[1][2]) << "\n";
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
