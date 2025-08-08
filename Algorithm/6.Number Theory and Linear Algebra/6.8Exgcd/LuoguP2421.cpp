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
ll sub(ll a, ll b, ll m) {
    return ((a - b) % m + m) % m;
}
void solve() {
    int n;
    cin >> n;
    vector<ll> C(n + 1), P(n + 1), L(n + 1);
    ll mx = 0;
    for(int i = 1; i <= n; i++) {
        cin >> C[i] >> P[i] >> L[i];
        mx = max(mx, C[i]);
        C[i]--;
    }
    for(int m = mx; ; m++) {
        bool ok = true;
        for(int i = 1; i <= n && ok; i++) {
            for(int j = i + 1; j <= n && ok; j++) {
                ll a = sub(P[i], P[j], m), b = sub(C[j], C[i], m), p = m;
                ll g = gcd(a, m);
                if(b % g != 0) continue;
                a /= g;
                b /= g;
                p /= g;
                ll t = b * mod_inv(a, p) % p;
                if(t <= min(L[i], L[j])) {
                    ok = false;
                }        
            }
        }
        if(ok) {
            cout << m << "\n";
            return;
        }
    }
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
