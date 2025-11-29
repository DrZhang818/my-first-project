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
    vector<int> a(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    vector<ll> dp(n + 1, inf);
    for(int i = 1; i <= n; i++) {
        ll cur = 0;
        for(int j = i - 1; j >= 1; j--) {
            if(a[j] <= a[i]) {
                dp[i] = min(dp[i], dp[j] + cur);
            }
            if(a[j] != a[i]) {
                cur += c[j];
            }
        }
        dp[i] = min(dp[i], cur);
    }
    map<int,ll> mp;
    ll cur = c[n];
    mp[a[n]] += c[n];
    ll ans = dp[n];
    for(int j = n - 1; j >= 1; j--) {
        cur += c[j];
        mp[a[j]] += c[j];
        ans = min(ans, dp[j] + cur - mp[a[j]]);
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
