#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<array<ll,2>> dp(2, {-inf,-inf});
    dp[0][0] = 0;
    ll ans = -inf;
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        ndp[0][1] = max(dp[0][1], dp[0][0]) + a[i];
        ndp[1][0] = max(dp[1][0], dp[0][1]);
        ndp[1][1] = max({dp[0][1], dp[1][0], dp[1][1]}) + a[i];
        dp = ndp;
        ans = max(ans, dp[1][1]);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
