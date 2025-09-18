#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int T;
    cin >> T;
    ll x = sqrt(2 * T);
    ll y = x + 1;
    auto p = [&](ll x) -> ll {
        return x * x - x + 2 * T;
    };
    auto q = [&](ll x) -> ll {
        return 2 * x;
    };
    ll a, b;
    if(p(x) * q(y) < p(y) * q(x)) {
        a = p(x), b = q(x);
    } else {
        a = p(y), b = q(y);
    }
    ll g = gcd(a, b);
    a /= g;
    b /= g;
    cout << a << " " << b << "\n";
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
