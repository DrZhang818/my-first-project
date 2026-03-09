#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int m, a, b;
    cin >> m >> a >> b;

    vector<vector<int>> dp(m, vector<int>(m, -1));
    vector<vector<bool>> vis(m, vector<bool>(m, false));

    auto dfs = [&](this auto&& self, int s1, int s2) -> bool {
        if(s1 == 0 || s2 == 0) {
            return false;
        }
        if(dp[s1][s2] != -1) {
            return dp[s1][s2];
        }
        if(vis[s1][s2]) {
            return true;
        }
        vis[s1][s2] = true;
        dp[s1][s2] = self(s2, (a * s2 + b * s1) % m);
        vis[s1][s2] = false;
        return dp[s1][s2];
    };

    int ans = 0;
    for(int x = 0; x <= m - 1; x++) {
        for(int y = 0; y <= m - 1; y++) {
            if(dfs(x, y)) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
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
