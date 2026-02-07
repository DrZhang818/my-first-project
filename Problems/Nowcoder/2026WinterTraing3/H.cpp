#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

db eps = 1E-3;

void solve() {  
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if(y1 == y2) {
        if(abs(x1 * y2 - x2 * y1) == 4) {
            cout << 0 << "\n";
        } else {
            cout << "no answer\n";
        }
        return;
    }

    db x = db(4 + x2 * y1 - x1 * y2) / (y1 - y2);
    if(abs(abs(x1 * y2 - x * y2 - x2 * y1 + x * y1) - 4) <= eps) {
        cout << fixed << setprecision(12) << x << "\n";
    } else {
        x = db(-4 + x2 * y1 - x1 * y2) / (y1 - y2);
        cout << fixed << setprecision(12) << x << "\n";
    }
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
