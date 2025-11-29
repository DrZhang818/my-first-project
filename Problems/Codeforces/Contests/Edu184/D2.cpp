#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ll V = ll(1E12);

void solve() {
    ll x, y, k;
    cin >> x >> y >> k;
    if(y == 1) {
        cout << -1 << "\n";
        return;
    }
    while(x > 0) {
        ll p = (k - 1) / (y - 1);
        if(p == 0) {
            break;
        }
        ll m = y - 1 - (k - 1 - p * (y - 1));
        ll t = min(x, (m + p - 1) / p);
        k += p * t;
        x -= t;
        if(k > V) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << k << "\n";
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
