#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 1E9 + 7;
constexpr int N = 2E5;

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
    int n, l, r;
    cin >> n >> l >> r;

    int d = min(r - n, 1 - l);
    int ans = (n % 2 ? 2LL : 1LL) * d * binom(n, n / 2) % MOD;

    for(int x = d + 1;; x++) {
        int i = max(1, x + l);
        int j = min(n, r - x);
        if(i > j + 1) break;
        add(ans, binom(j - i + 1, n / 2 - i + 1));
        if(n & 1) {
            add(ans, binom(j - i + 1, (n + 1) / 2 - i + 1));
        }
    }    

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}