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
ll mod_inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
void solve() {
    ll n, p, w, d;
    cin >> n >> p >> w >> d;
    ll g = gcd(w, d);
    if(p % g != 0) {
        cout << -1 << "\n";
        return;
    }
    p /= g;
    w /= g;
    d /= g;
    ll y = p % w * mod_inv(d, w) % w;
    ll x = (p - d * y) / w;
    if(x >= 0 && x + y <= n) {
        cout << x << " " << y << " " << n - x - y << "\n";
    } else {
        cout << -1 << "\n";
    }
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
