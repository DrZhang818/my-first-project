#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/28258/G
struct info {
    int v, w;
};
void solve() {
    int n, m, rt;
    cin >> n >> m >> rt;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<int> dp(n + 1);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        if(u != rt && adj[u].size() == 1) {
            dp[u] = inf;
            return;
        }
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            dp[u] += min(dp[v], w);
        }
    };
    dfs(dfs, rt, 0);
    cout << dp[rt] << "\n";
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
