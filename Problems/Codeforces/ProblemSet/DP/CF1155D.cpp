#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    array<ll,3> dp;
    dp[0] = 0;
    dp[1] = dp[2] = -inf;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        array<ll,3> ndp;
        ndp[0] = max({0LL, dp[0], dp[1]}) + a[i];
        ndp[1] = max({0LL, dp[1], dp[2]}) + a[i] * x;
        ndp[2] = max(0LL, dp[2]) + a[i];
        swap(dp, ndp);
        ans = max({ans, dp[0], dp[1], dp[2]});
    }
    cout << ans << "\n";
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
