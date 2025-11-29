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

    auto ck = [&](ll val) -> bool {
        for(ll i = 0; i < x; i++) {
            val = val - val / y;
        }
        return val >= k;
    };

    ll l = 0, r = V + 1;
    while(l + 1 < r) {
        ll mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if(r == V + 1) {
        cout << -1 << "\n";
        return;
    }
    cout << r << "\n";
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
