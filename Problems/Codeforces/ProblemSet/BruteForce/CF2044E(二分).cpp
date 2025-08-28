#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;
    auto ckL = [&](ll x, ll t) -> bool {
        return x * t >= l2;
    };
    auto ckR = [&](ll x, ll t) -> bool {
        return x * t <= r2;
    };
    ll ans = 0;
    for(ll cur = 1; cur <= inf; cur *= k) {
        int l = l1 - 1, r = r1 + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ckL(mid, cur)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        int L = r;
        l = l1 - 1, r = r1 + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ckR(mid, cur)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        int R = l;
        ans += R - L + 1;
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
