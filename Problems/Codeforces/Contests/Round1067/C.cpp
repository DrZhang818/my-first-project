#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = 1E18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    ll mx = -inf;
    vector<ll> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = max(dp[i - 1], 0LL) + a[i];
        mx = max(mx, dp[i]);
    }
    if(k % 2 == 0) {
        cout << mx << "\n";
        return;        
    }
    vector<ll> g(n + 1);
    ll ans = -inf;
    for(int i = 1; i <= n; i++) {
        g[i] = max({dp[i], g[i - 1] + a[i], dp[i - 1] + a[i] + b[i], a[i] + b[i]});
        ans = max(ans, g[i]);
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
