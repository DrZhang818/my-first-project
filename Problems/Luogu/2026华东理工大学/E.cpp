#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;
constexpr int MOD = 998244353;
constexpr int inv2 = MOD + 1 >> 1;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int minp[N + 1], g[N + 1], preg[N + 1];
vector<int> primes;

auto isqrt(i64 n) {
    i64 x = sqrtl(n);
    while((x + 1) * (x + 1) <= n) x++;
    while(x * x > n) x--;
    return x;
}

auto T(i64 x) {
    x %= MOD;
    return 1LL * x * (x + 1) / 2 % MOD;
}

auto calc(i64 n) {
    i64 sq = isqrt(n);
    
    int res = 0;
    for(i64 l = 1, r; l <= sq; l = r + 1) {
        i64 v = n / (l * l);
        r = isqrt(n / v);
        int sum = (preg[r] + MOD - preg[l - 1]) % MOD;
        add(res, 1LL * sum * T(n / (1LL * l * l)) % MOD);
    }

    return res;
}

void solve() {
    i64 l, r;
    cin >> l >> r;

    int ans = calc(r);
    add(ans, MOD - calc(l - 1));

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    g[1] = 1;
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
            g[i] = (1 + MOD - 1LL * i * i % MOD) % MOD;
        }
        for(int p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) {
                g[i * p] = g[i];
                break;
            } else {
                g[i * p] = 1LL * g[i] * g[p] % MOD;
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        preg[i] = (preg[i - 1] + g[i]) % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
