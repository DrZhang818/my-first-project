#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] - a[i];
    }
    vector<ll> dp(n + 1);
    dp[1] = a[1];
    ll mx = dp[1] - pre[1];
    for(int i = 2; i <= n; i++) {
        dp[i] = mx + pre[i - 1] + a[i];
        mx = max(mx, dp[i] - pre[i]);
    }
    ll ans = -inf;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, dp[i] - a[i] + pre[n] - pre[i]);
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
