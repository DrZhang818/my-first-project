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
ll mod(ll a, ll m) {
    return (a % m + m) % m;
}
ll mod_inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    c = -c;
    if(a < 0) {
        a = -a;
        b = -b;
        c = -c;
    }
    ll g = abs(gcd(a, b));
    if(c % g != 0) {
        cout << -1 << "\n";
        return;
    }
    if(a == 0) {
        cout << 0 << " " << c / b << "\n";
        return;
    }
    a /= g;
    b /= g;
    c /= g;
    ll y = mod(c, a) * mod_inv(mod(b, a), a) % a;
    ll x = (c - b * y) / a;
    cout << x << " " << y << "\n";
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
