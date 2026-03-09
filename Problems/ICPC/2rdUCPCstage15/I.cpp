#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int a, b, m;
    cin >> a >> b >> m;

    vector<i64> dp(m + 1);
    dp[0] = 320;
    int r = (a - b % a) % a;

    for(int i = 1; i <= m; i++) {
        dp[i] = dp[i - 1];
        if(i - a >= 0) {
            dp[i] = max(dp[i], dp[i - a] + 160);
        }
        if(i - b >= 0) {
            dp[i] = max(dp[i], dp[i - b] + b / a * 160LL + 160);
        }
        if(i - b - r >= 0) {
            dp[i] = max(dp[i], dp[i - b - r] + (b + r) / a * 160LL + 160);
        }
    }
    cout << dp[m] << "\n";
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
