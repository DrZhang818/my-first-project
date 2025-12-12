#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<array<ll,2>> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i][0] = min(dp[i - 1][0] - a[i], b[i] - dp[i - 1][1]);
        dp[i][1] = max(dp[i - 1][1] - a[i], b[i] - dp[i - 1][0]);
    }
    cout << dp[n][1] << "\n";
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
