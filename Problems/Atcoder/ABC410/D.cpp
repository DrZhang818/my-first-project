#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    vector<array<bool, 1 << 10>> dp(n + 1);
    dp[1][0] = 1;
    queue<info> q;
    q.push({1, 0});
    while(!q.empty()) {
        auto [u, s] = q.front(); q.pop();
        for(auto [v, w] : adj[u]) {
            if(dp[v][s ^ w]) continue;
            dp[v][s ^ w] = true;
            q.push({v, s ^ w});
        }
    }
    for(int i = 0; i < 1 << 10; i++) {
        if(dp[n][i]) {
            cout << i << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
