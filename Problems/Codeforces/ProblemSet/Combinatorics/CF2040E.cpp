#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int P = 998244353;

void solve() {
    int n, q;
    cin >> n >> q;
    vector adj(n + 1, vector<int>{});
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector dp(n + 1, vector(n + 1, array<ll,2>{-1, -1}));
    for(int j = 0; j <= n; j++) dp[1][j][0] = dp[1][j][1] = 0;
    vector<int> fa(n + 1);
    [&](this auto &&self, int u, int p) -> void {
        for(int v : adj[u]) {
            if(v != p) {
                fa[v] = u;
                self(v, u);
            }
        }
    } (1, 0);

    auto dfs = [&](this auto &&self, int u, int c, int s) -> ll {
        if(dp[u][c][s] != -1) {
            return dp[u][c][s];
        }
        int p = fa[u];
        if(s == 1) {
            dp[u][c][s] = self(p, c, s ^ 1) + 1;
        } else {
            int d = adj[u].size();
            ll cur = self(p, c, s ^ 1) + 1 + 2LL * (d - 1);
            dp[u][c][s] = cur; 
            if(c >= 1) {
                dp[u][c][s] = min(dp[u][c][s], self(p, c - 1, s ^ 1) + 1);
            }
        }
        return dp[u][c][s];
    };

    for(int i = 2; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int s = 0; s <= 1; s++) {
                if(dp[i][j][s] == -1) {
                    dfs(i, j, s);
                }
            }
        }
    }
    while(q--) {
        int v, p;
        cin >> v >> p;
        cout << dp[v][p][1] % P << "\n";
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
