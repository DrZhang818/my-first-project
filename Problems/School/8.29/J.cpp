#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 2E18;

ll fastPow(ll a, int b){
    ll ans = 1;
    while(b > 0){
        if(b & 1) {
            if(ans > inf / a) {
                ans = inf;
                break;
            }
            ans *= a;
        }
        if(a > inf / a) {
            a = inf + 1;
        } else {
            a *= a;
        }
        b >>= 1;
    }
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    if(n < 4) {
        cout << 1 << "\n";
        return;
    }
    ll ans = 1;
    set<ll> st;
    for(int b = 2; b <= 64; b++) {
        if(b == 2) {
            ll L = 2;
            ll l = 2, r = n + 1; 
            while(l + 1 < r) {
                ll mid = l + r >> 1;
                if(fastPow(mid, b) <= n) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            ll R = l;
            ans += R - L + 1;
        } else {
            for(ll x = 2; x <= n; x++) {
                ll y = fastPow(x, b);
                if(y > n) {
                    break;
                }
                ll t = sqrt(y);
                if(t * t != y && (t + 1) * (t + 1) != y && !st.contains(y)) {
                    ans++;
                    st.insert(y);
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
