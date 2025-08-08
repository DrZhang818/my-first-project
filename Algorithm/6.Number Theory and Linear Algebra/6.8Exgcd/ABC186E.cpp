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
ll mod(ll a, ll p) {
    return (a % p + p) % p;
}
ll mod_inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
void solve() {
    ll n, s, k;
    cin >> n >> s >> k;
    ll a = k, b = -s, p = n;
    ll g = gcd(a, p);
    if(b % g != 0) {
        cout << -1 << "\n";
        return;
    }
    a /= g;
    b /= g;
    p /= g;
    cout << mod(b, p) * mod_inv(mod(a, p), p) % p << "\n";
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
