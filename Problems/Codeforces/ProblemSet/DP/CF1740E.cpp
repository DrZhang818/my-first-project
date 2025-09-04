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
    vector<vector<int>> adj(n + 1);
    for(int v = 2; v <= n; v++) {
        int u;
        cin >> u;
        adj[u].push_back(v);
    }
    vector<array<int,2>> dp(n + 1);
    auto dfs = [&](this auto &&self, int u) -> void {
        dp[u][1] = 1;
        for(int v : adj[u]) {
            self(v);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] = max(dp[u][1], dp[v][1] + 1);
        }
    };
    dfs(1);
    cout << max(dp[1][0], dp[1][1]) << "\n";
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
