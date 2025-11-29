#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 200000;
const int inv2 = MOD + 1 >> 1;

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

int powiv2[N + 1];

int inv(int x) {
    return fast_pow(x, MOD - 2);
}

int C(int n, int m) {
    if(n < m) return 0;
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int B, W;
    cin >> B >> W;
    int pB = 0, pW = 0;
    for(int i = 1; i <= B + W; i++) {
        add(pB, 1LL * powiv2[i - 1] * C(i - 2, B - 1) % MOD);
        add(pW, 1LL * powiv2[i - 1] * C(i - 2, W - 1) % MOD);
        int rem = ((1LL - pB - pW) % MOD + MOD) % MOD;
        int ans = (1LL * inv2 * rem % MOD + pW) % MOD;
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    powiv2[0] = 1;
    for(int i = 1; i <= N; i++) {
        powiv2[i] = 1LL * inv2 * powiv2[i - 1] % MOD;
    }

    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
