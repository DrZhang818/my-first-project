#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] ^ a[i];
    }
    vector<i64> dp(n + 1, inf);
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        i64 mn = inf;
        for(int j = i - 1; j >= 0; j--) {
            mn = min(mn, dp[j]);
            dp[i] = min(dp[i], mn + (pre[i] ^ pre[j]));
        }
    }
    cout << dp[n] << "\n";
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
