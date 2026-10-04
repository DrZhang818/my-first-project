#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 1E9 + 7;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> dp(n + 1, 1);
    for(int i = 2; i <= k; i++) {
        vector<int> ndp(n + 1);
        ndp[n] = 1;
        for(int j = n - 1; j >= 0; j--) {
            ndp[j] = (ndp[j + 1] + dp[n - j]) % MOD;
        }
        dp = move(ndp);
    }
    cout << dp[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}