#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P3807
vector<int> fac, inv_fac;
int fast_pow(int a, int b, int MOD) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x, int MOD) {
    return fast_pow(x, MOD - 2, MOD);
}
void init(int p) {
    fac.resize(p);
    inv_fac.resize(p);
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i < p; i++) {
        fac[i] = 1LL * fac[i - 1] * i % p;
    }
    inv_fac[p - 1] = inv(fac[p - 1], p);
    for(int i = p - 2; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % p;
    }
}
int C(int n, int m, int p) {
    if(m > n) return 0;
    return 1LL * fac[n] * inv_fac[m] % p * inv_fac[n - m] % p;
}
int Lucas(int n, int m, int p) {
    if(m == 0) return 1;
    return 1LL * C(n % p, m % p, p) * Lucas(n / p, m / p, p) % p;
}
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    init(p);
    cout << Lucas(n + m, n, p) << "\n";
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
