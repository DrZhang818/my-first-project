#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<i64> dp(n + 1);
    for(int i = 2; i <= n; i++) {
        i64 x = a[i - 1], y = a[i];
        if(y < x) {
            while(y < x) {
                if(y == 1) {
                    cout << -1 << "\n";
                    return;
                }
                dp[i]++;
                y *= y;
            }
        } else {
            while(x != 1 && x * x <= y) {
                dp[i]--;
                x *= x;
            }
        }
    }

    i64 ans = 0;
    for(int i = 1; i <= n; i++) {
        dp[i] += dp[i - 1];
        dp[i] = max(dp[i], 0LL);
        ans += dp[i];
    }

    cout << ans << "\n";
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
