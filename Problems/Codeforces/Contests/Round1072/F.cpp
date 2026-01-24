#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector adj(n + 1, vector<int>{});
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<array<int,3>> dp(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        if(adj[u].size() > 1 || u == 1) {
            dp[u][0] = 1;
            for(int v : adj[u]) {
                if(v == fa) continue;
                self(v, u);
                array<int,3> ndp {};
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        ndp[(i + j) % 3] |= dp[u][i] & dp[v][j];
                    }
                }
                swap(dp[u], ndp);
            }
        } 
        dp[u][1] |= 1;
    };
    dfs(1, 0);
    if(dp[1][0]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
 