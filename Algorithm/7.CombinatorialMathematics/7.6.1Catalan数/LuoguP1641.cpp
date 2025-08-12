#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 20100403;

vector<int> fac, inv_fac;
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void init(int n) {
    fac.resize(n + 1);
    inv_fac.resize(n + 1);
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[n] = inv(fac[n]);
    for(int i = n - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }
}
int C(int n, int m) {
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}
int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}
void solve() {
    int n, m;
    cin >> n >> m;
    init(n + m);
    cout << mod(C(n + m, m) - C(n + m, m - 1)) << "\n";
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
