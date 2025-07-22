#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

void solve() {
    ll n;
    cin >> n;
    auto ck = [&](ll x, int k) -> int {
        ll res = 0, cur = 1;
        for(int i = 0; i <= k; i++) {
            res += cur;
            if(cur > inf / x) cur = inf;
            else cur *= x;
            if(res > n) return 1;
        }
        return res == n ? 2 : 0;
    };
    for(int k = 2; k <= 60; k++) {
        ll l = 1, r = inf;
        while(l + 1 < r) {
            ll mid = l + (r - l) / 2;
            int tag = ck(mid, k);
            if(tag == 1) {
                r = mid;
            } else if(tag == 0) {
                l = mid;
            } else {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
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
