#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 2, 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    

    vector<vector<i64>> dp(n + 2, vector<i64>(n + 2));

    for(int len = 2; len <= n + 1; len++) {
        for(int l = 0; l + len < n + 2; l++) {
            int r = l + len;
            i64 mx = 0;
            for(int i = l + 1; i < r; i++) {
                mx = max(mx, dp[l][i] + dp[i][r] + a[l] * a[i] * a[r]);
            }
            dp[l][r] = mx;
        }
    }

    cout << dp[0][n + 1] << "\n";
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