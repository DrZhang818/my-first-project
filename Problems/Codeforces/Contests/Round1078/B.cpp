#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    ll x, y;
    cin >> n >> x >> y;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<ll> pre(n + 2), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i] / x * y;
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + a[i] / x * y;
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, a[i] + pre[i - 1] + suf[i + 1]);
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
