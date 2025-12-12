#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = 0, S = a[1];
    for(int i = 2; i <= n; i++) {
        if(100 * a[i] - k * S >= 0) {
            ll x = (100 * a[i] - k * S + k - 1) / k;
            ans = max(ans, x);
        }
        S += a[i];
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
