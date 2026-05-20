#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<array<db, 2>> dp(n + 1, {1E18, 1E18});

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        db sum = 0;
        vector<db> val;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sum += dp[v][1];
            if(dp[v][0] != 1E18) {
                val.push_back(dp[v][0] - dp[v][1]);
            }
        }
        int m = val.size();
        if(s[u] == '1') {
            dp[u][0] = dp[u][1] = sum;
        } else {
            sort(val.begin(), val.end());
            dp[u][1] = sum + (db)deg[u];
            for(int y = 1; y <= m; y++) {
                sum += val[y - 1];
                dp[u][0] = min(dp[u][0], sum + (db)deg[u] / y);
                dp[u][1] = min(dp[u][1], sum + (db)deg[u] / (y + 1));
            }
        }
    };
    dfs(1, 0);

    cout << fixed << setprecision(12) << dp[1][0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}