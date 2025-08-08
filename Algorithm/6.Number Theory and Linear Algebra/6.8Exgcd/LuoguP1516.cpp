#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P1516
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
ll up(ll a, ll b) {
    ll res = a / b;
    if(a % b != 0 && (a > 0) == (b > 0)) {
        res++;
    }
    return res;
}
void solve() {
    ll x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;
    ll a = ((m - n) % L + L) % L, b = L, c = (y - x + L) % L;
    ll g = gcd(a, b);
    if(c % g != 0) {
        cout << "Impossible\n";
        return;
    }   
    a /= g;
    b /= g;
    exgcd(a, b, x, y);
    x *= c / g;
    x += b * up(-x + 1, b);
    cout << x << "\n";
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
