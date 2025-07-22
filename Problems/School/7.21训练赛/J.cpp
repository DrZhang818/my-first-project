#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto ck = [&](ll x) -> bool {
        auto b = a;
        if(x == 0) return true;
        ll cnt = 0;
        for(int i = 1; i <= n; i++) {
            cnt += b[i] / x;
            b[i] %= x;
            if(b[i] + b[i + 1] >= x) {
                cnt++;
                b[i + 1] -= x - b[i];
            }
        }
        return cnt >= k;
    };
    ll l = -1, r = 1e18 / k;
    while(l + 1 < r) {
        ll mid = l + (r - l) / 2;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << k * l << "\n";
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
