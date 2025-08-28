#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<array<ll,2>> dp(n + 1);
    dp[1][0] = dp[1][1] = a[1];
    for(int i = 2; i <= n; i++) {
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
        dp[i][0] = dp[i - 1][1] + max(0, a[i] - i + 1);
        dp[i][0] = min(dp[i][0], dp[i - 1][0] + a[i] - 1);
    }
    cout << min(dp[n][0], dp[n][1]) << "\n";
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
