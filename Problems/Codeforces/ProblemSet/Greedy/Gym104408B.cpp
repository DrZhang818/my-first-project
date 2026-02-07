#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr db pi = 3.141592653589793;

void solve() {  
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    if(x1 == 0 && x2 == 0) {
        cout << abs(y1 - y2) << "\n";
    } else if(y1 == 0 && y2 == 0) {
        cout << abs(x1 - x2) << "\n";
    } else {
        ll a = abs(x1 == 0 ? y1 : x1);
        ll b = abs(x2 == 0 ? y2 : x2);
        ll d = abs(a - b);
        ll r = min(a, b);
        db ans = 0.5 * pi * r + d;
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
