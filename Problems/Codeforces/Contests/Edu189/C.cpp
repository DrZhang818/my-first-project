#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string x, y;
    cin >> x >> y;

    array<int, 2> dp {};
    dp[1] = x[0] != y[0];

    for(int i = 1; i < n; i++) {
        array<int, 2> ndp {};
        ndp[0] = min(dp[0] + 1, dp[1]);
        ndp[1] = min(dp[0] + (x[i] != x[i - 1]) + (y[i] != y[i - 1]), dp[1] + (x[i] != y[i]));
        dp = move(ndp);
    }

    cout << min(dp[0] + 1, dp[1]) << "\n";
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