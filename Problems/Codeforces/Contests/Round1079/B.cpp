#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    const int sq = sqrt(n);

    ll ans = 0;

    for(int i = 1; i <= n; i++) {
        ll x = a[i];
        if(x > sq) {
            int d = i % a[i];
            int p = 0;
            for(int j = d; j < i; j += x) {
                if(a[i] * a[j] == i - j) {
                    ans++;
                    p++;
                }
            }
        }

        for(ll v = 1; v <= sq; v++) {
            ll t = a[i] * v + i;
            if(t <= n) {
                if(v == a[t]) {
                    ans++;
                }
            } else {
                break;
            }
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
