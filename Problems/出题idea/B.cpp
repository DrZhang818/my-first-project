#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
using ldb = long double;
constexpr int inf = 1000000000;
constexpr ldb eps = 1E-8;

void solve() {
    ll t1, t2, l, t0, v, k, x, y;
    cin >> t1 >> t2 >> l >> t0 >> v >> k >> x >> y;
    ll p = x * v + y * k * t0 - y * k * t1;
    ldb min_h = ldb(l * t0 - l * t2) / (t1 - t0);
    if(min_h - v + l >= eps) {
        cout << -1 << "\n";
        return;
    }
    if(p >= 0) {
        ll max_h = v - l;
        ll ans = p * max_h + x * l * v - y * k * l * t2 + y * k * t0 * l;
        cout << ans << "\n";
    } else {
        min_h = max(min_h, ldb(0));
        ldb ans = p * min_h + x * l * v - y * k * l * t2 + y * k * t0 * l;
        cout << fixed << setprecision(12) << ans << "\n";
    }
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
