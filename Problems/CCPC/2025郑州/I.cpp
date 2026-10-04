#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;
constexpr int inv2 = (MOD + 1) >> 1;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

constexpr int N = 5000;
int fac[N + 1], ifac[N + 1];
auto init = [] {
    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    ifac[N] = power(fac[N], MOD - 2);
    for(int i = N; i; i--) {
        ifac[i - 1] = 1LL * ifac[i] * i % MOD;
    }
    return 0;
}();

int binom(int n, int r) {
    if(r < 0 || n < r) return 0;
    return 1LL * fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;

    int invn = power(n, MOD - 2);

    int ans = power(2, n - 1);
    vector<int> pw(n, 1);

    vector<int> sum(k + 1);
    for(int i = 0; i <= k; i++) {
        int dp = 1;
        for(int j = 1; j < n; j++) {
            add(dp, 1LL * dp * pw[j] % MOD);
            pw[j] = 1LL * pw[j] * j % MOD;
        }
        sum[i] = dp;
    }

    int facni = 1;

    int S = 0;
    for(int i = 0; i <= k; i++) {
        if((k - i) & 1) {
            add(S, MOD - 1LL * binom(k, i) * facni % MOD * sum[k - i] % MOD);
        } else {
            add(S, 1LL * binom(k, i) * facni % MOD * sum[k - i] % MOD);
        }
        facni = 1LL * facni * fac[n] % MOD;
    }
    S = 1LL * S * power(ifac[n], k) % MOD;

    add(ans, MOD - S);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}