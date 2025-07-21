#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<ll> dp(n + 1, -inf);
    for(int i = k; i <= n; i++) {
        dp[i] = max(dp[i - 1], pre[i] - pre[i - k]);
    }
    ll ans = -inf;
    for(int i = 2 * k; i <= n; i++) {
        ans = max(ans, pre[i] - pre[i - k] + dp[i - k]);
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
