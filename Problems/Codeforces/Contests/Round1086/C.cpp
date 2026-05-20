#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1), p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i] >> p[i];
    }    

    vector<db> dp(n + 1);
    dp[n] = c[n];
    for(int i = n - 1; i >= 1; i--) {
        dp[i] = max(dp[i + 1], c[i] + (1 - db(p[i]) / 100) * dp[i + 1]);
    }

    cout << fixed << setprecision(12) << dp[1] << "\n";
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
