#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

vector<vector<int>> dp(21, vector<int>(23, inf));
auto dfs(int n, int m) -> int {
    if(n == 1 && m == 1) {
        return 4;
    }
    if(dp[n][m] != inf) return dp[n][m];
    int& res = dp[n][m];

    for(int i = 1; i < n; i++) {
        res = min(res, dfs(i, m) + dfs(n - i, m) - 3);
    }
    for(int j = 1; j < m; j++) {
        res = min(res, dfs(n, j) + dfs(n, m - j) - 3);
    }

    return res;
};

void solve() {
    cout << dfs(20, 22) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}