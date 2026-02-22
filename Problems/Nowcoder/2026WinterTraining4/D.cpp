#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

using i128 = __int128;

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= (i128)a / b * x;
    return g;
}

ll mod_inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
ll get(ll a, ll b, ll c) {
    b = (b % c + c) % c;
    ll g = gcd(a, c);
    if(b % g != 0) {
        return -1;
    }
    a /= g;
    b /= g;
    c /= g;
    return (i128)b * mod_inv(a, c) % c;
}

void solve() {  
    ll a, b, L;
    cin >> L >> a >> b;

    ll g = gcd(a, b);

    if(L % g) {
        cout << "No\n";
        return;
    }

    a /= g;
    b /= g;
    L /= g;

    i128 x = get(a, L, b);
    i128 y = (L - ((i128)a * x)) / b;

    if(y < 0) {
        cout << "No\n";
        return;
    }

    i128 t = (y - x) / (a + b);

    ll mn = numeric_limits<ll>::max();

    ll X = -1, Y = -1;

    for(int i = 0; i <= 1; i++) {
        i128 cur = t + i;
        i128 curx = x + (i128)b * cur;
        i128 cury = y - (i128)a * cur;

        if(curx < 0 || cury < 0) continue;

        if(max(curx, cury) < mn) {
            mn = max(curx, cury);
            X = curx;
            Y = cury;
        }
    }

    cout << "Yes\n";
    cout << X << " " << Y << "\n";

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
