#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/28258/E
struct info {
    int v, w;
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector dp(n + 1, vector<int>(k + 1));
    auto dfs = [&](auto &&self, int u, int fa, int s) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            for(int i = 0; i < s; i++) {
                dp[v][i] = dp[u][i] + w;
            }
            self(self, v, u, s - 1);
            for(int i = 1; i <= s; i++) {
                dp[u][i] = max(dp[u][i], dp[v][i - 1]);
            }
        }
    };
    dfs(dfs, 1, 0, k);
    cout << dp[1][k] << "\n";
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
