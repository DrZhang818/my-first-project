#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int MOD = 1E9 + 7;

int power(int a, int b, int m) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return res;
}

int inv(int x) {
    return power(x, MOD - 2, MOD);
}

vector<int> fac, invfac;

void init(int n) {
    fac.resize(n + 1);
    invfac.resize(n + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    invfac[n] = inv(fac[n]);
    for(int i = n - 1; i >= 1; i--) {
        invfac[i] = 1LL * invfac[i + 1] * (i + 1) % MOD;
    }
}

int binom(int n, int m) {
    if(n < m || m < 0) return 0;
    return 1LL * fac[n] * invfac[m] % MOD * invfac[n - m] % MOD;
}

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;

    init(n);

    int ans = 0;
    for(int i = k, s = 1; i <= n; i++, s ^= 1) {
        int cur = 1LL * binom(i, k) * binom(n, i) % MOD * power(2, power(2, n - i, MOD - 1), MOD) % MOD;
        if(s) {
            add(ans, cur);
        } else {
            add(ans, MOD - cur);
        }
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
