#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll mul(ll a, ll b, ll m) {
    ll res = 0;
    while(b) {
        if(b & 1) res = (res + a) % m;
        a = (a + a) % m;
        b >>= 1;
    }
    return res;
}
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
ll inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
ll mod(ll a, ll p) {
    return (a % p + p) % p;
}
ll get(ll a, ll b, ll c) {
    return mul(b, inv(a, c), c);
}
void solve() {
    int n;
    cin >> n;
    vector<ll> M(n + 1), A(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> M[i] >> A[i];
    }
    ll ans = A[1], m = M[1];
    for(int i = 2; i <= n; i++) {
        ll a = m, b = mod(A[i] - ans, M[i]), c = M[i];
        ll g = gcd(a, c);
        a /= g;
        b /= g;
        c /= g;
        ll t = get(a, b, c);
        ans = (ans + mul(m, t, m * c)) % (m * c);
        m *= c;
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
