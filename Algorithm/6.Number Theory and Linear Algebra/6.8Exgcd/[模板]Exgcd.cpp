#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll down(ll a, ll b) {
    ll res = a / b;
    if(a % b != 0 && (a > 0) != (b > 0)) {
        res--;
    }
    return res;
}
ll up(ll a, ll b) {
    ll res = a / b;
    if(a % b != 0 && (a > 0) == (b > 0)) {
        res++;
    }
    return res;
}
void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    ll g = gcd(a, b);
    a /= g;
    b /= g;
    if(c % g != 0) {
        cout << -1 << "\n";
        return;
    }
    ll x, y;
    exgcd(a, b, x, y);
    x *= c / g;
    y *= c / g;
    ll lo = up(-x + 1, b);
    ll hi = down(y - 1, a);
    ll mnx = x + b * lo;
    ll mxx = x + b * hi;
    ll mny = y - a * hi;
    ll mxy = y - a * lo;
    if(lo <= hi) {
        cout << hi - lo + 1 << " " << mnx << " " << mny << " " << mxx << " " << mxy << "\n";
    } else {
        cout << mnx << " " << mny << "\n";
    }
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
