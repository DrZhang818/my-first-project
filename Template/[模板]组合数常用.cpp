const int MOD = 998244353;
const int N = 5005;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int fac[N + 1], inv_fac[N + 1];
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
int C(int n, int m) {
    if(n < 0 || n < m) return 0;
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

void init() {
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }
}
