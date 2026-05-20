#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve(int n) {
    vector<vector<i64>> dp(n + 1, vector<i64>(n + 1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            dp[i][j] = j * dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
    i64 ans = accumulate(dp[n].begin(), dp[n].end(), 0LL);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin >> n) {
        solve(n);
    }
    return 0;
}