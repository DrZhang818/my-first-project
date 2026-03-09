#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void chmax(i64& x, i64 y) { if(x < y) x = y; }

void solve() {  
    int n, x, y, t;
    cin >> n >> x >> y >> t;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<vector<i64>> dp(n + 1, vector<i64>(t + 1));

    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for(int j = 0; j <= t; j++) {
            for(int k = 1; j + x + k * y <= t && k <= a[i]; k++) {
                chmax(dp[i][j + x + k * y], dp[i - 1][j] + 1LL * k * b[i]);
            }
        }
    }

    vector<int> ans(n + 1);
    for(int i = n; i >= 1; i--) {
        if(dp[i][t] == dp[i - 1][t]) {
            continue;
        }
        for(int j = 1; j <= a[i]; j++) {
            assert(t >= x + j * y);
            if(dp[i][t] == dp[i - 1][t - x - j * y] + 1LL * j * b[i]) {
                ans[i] = j;
                t -= x + j * y;
                break;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
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
