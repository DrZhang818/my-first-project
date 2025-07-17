#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
const int inv2 = (MOD + 1) >> 1;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    ll n;
    cin >> n;
    int u, v, w;
    u = v = w = 0;
    v = (n - 1) % MOD * ((n - 2) % MOD) % MOD * inv2 % MOD;
    for(ll L = 2, R; L <= n - 1; L = R + 1) {
        ll div = n / L;
        R = n / div;
        R = min(R, n - 1);
        add(u, div % MOD * ((L + R - 2) % MOD) % MOD * ((R - L + 1) % MOD) % MOD * inv2 % MOD);
        ll x = n % L, y = n % R;
        add(w, (x + y) % MOD * (((x - y) / div + 1) % MOD) % MOD * inv2 % MOD);
    }
    cout << (((ll)u - v + w) % MOD + MOD) % MOD << "\n";
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
