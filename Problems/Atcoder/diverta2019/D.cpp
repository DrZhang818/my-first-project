#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n;
    cin >> n;
    ll ans = 0;
    ll m = n - 1;
    if(m > 0 && n / m == n % m) {
        ans += m;
    }
    for(ll d = 2; d * d <= n; d++) {
        if(n % d == 0) {
            ll m = d - 1;
            if(n / m == n % m) {
                ans += m;
            }
            if(d * d != n) {
                m = n / d - 1;
                if(n / m == n % m) {
                    ans += m;
                }
            }
        }
    }
    cout << ans << "\n";
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
