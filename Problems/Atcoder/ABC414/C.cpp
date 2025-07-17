#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int a;
    ll n;
    cin >> a >> n;
    auto ck = [&](ll x) -> bool {
        string s;
        while(x) {
            s += to_string(x % a);
            x /= a;
        }
        string t = s;
        reverse(s.begin(), s.end());
        return s == t;
    };
    ll ans = 0;
    for(ll i = 1; i <= 999999; i++) {
        string s = to_string(i);
        string t = s;
        reverse(s.begin(), s.end());
        t += s;
        ll x = stoll(t);
        if(x > n) break;
        if(ck(x)) {
            ans += x;
        }
    }
    for(ll i = 1; i <= 9 && i <= n; i++) {
        if(ck(i)) {
            ans += i;
        }
    }
    for(ll i = 1; i <= 999999; i++) {
        string s = to_string(i);
        bool ok = true;
        for(char j = '0'; j <= '9'; j++) {
            string t = s;
            string p = s;
            reverse(p.begin(), p.end());
            t += j;
            t += p;
            ll x = stoll(t);
            if(x > n) {
                ok = false;
                break;
            }
            if(ck(x)) {
                ans += x;
            }
        }
        if(!ok) break;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
