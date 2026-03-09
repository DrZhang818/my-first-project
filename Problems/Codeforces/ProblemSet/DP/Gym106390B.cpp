#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {  
    int n;
    cin >> n;
    auto adj = vector<vector<pair<int,int>>>(n + 1);

    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    queue<int> q;
    q.push(1);

    vector<array<i64, 2>> dp(n + 1, {inf, inf});
    dp[1][0] = dp[1][1] = 0;

    i64 mn = inf;
    while(!q.empty()) {
        int sz = q.size();
        i64 nxt_mn = inf;
        while(sz--) {
            int u = q.front(); q.pop();
            dp[u][1] = min(dp[u][1], mn);
            for(auto [v, w] : adj[u]) {
                if(dp[v][0] != inf) continue;
                dp[v][0] = dp[u][0] + w;
                dp[v][1] = dp[u][1] + w;
                nxt_mn = min(nxt_mn, dp[v][0]);
                q.push(v);
            }
        }
        mn = nxt_mn;
    }

    for(int i = 1; i <= n; i++) {
        cout << min(dp[i][0], dp[i][1]) << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
