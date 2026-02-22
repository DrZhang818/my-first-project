#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n, a, b;
    cin >> n >> a >> b;

    ll ans = 0;

    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 8; j++) {
            if(8 * i + 7 * j > n) {
                continue;
            }
            ll cur = (a + b) * i + a * j;
            ll u = 7 * (a + b), v = 8 * a;
            ll mx = max(u, v);
            cur += (n - 8 * i - 7 * j) / 56 * mx;
            ans = max(ans, cur);
        }
    }

    for(int i = 0; i < 1; i++) {
        for(int j = 0; j < 4; j++) {
            if(8 * i + 2 * j > n) {
                continue;
            }
            ll cur = (a + b) * i + b * j;
            ll u = (a + b), v = 4 * b;
            ll mx = max(u, v);
            cur += (n - 8 * i - 2 * j) / 8 * mx;
            ans = max(ans, cur);
        }
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
