#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

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

vector<int> fac, inv_fac;

void init(int N) {
    fac.resize(N + 1);
    inv_fac.resize(N + 1);
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }
}

int C(int n, int m) {
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

void solve() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    init(n);
    auto work1 = [&]() -> void {
        vector<int> dp(n + 1);
        dp[0] = 1;
        for(auto x : {a, b, c}) {
            for(int i = x; i <= n; i++) {
                add(dp[i], dp[i - x]);
            }
        }
        cout << dp[n] << "\n";
    };

    auto work2 = [&]() -> void {
        int ans = 0;
        if(1LL * a * b >= sqrt(n)) {
            for(int ax = 0; ax <= n; ax += a) {
                for(int by = 0; by <= n - ax; by += b) {
                    if((n - ax - by) % c) {
                        continue;
                    }
                    add(ans, 1LL * C(n, ax) * C(n - ax, by) % MOD);
                }
            }
        } else {
            vector dp(n + 1, vector(a, vector<int>(b)));
            dp[0][0][0] = 1;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < a; j++) {
                    for(int k = 0; k < b; k++) {
                        add(dp[i + 1][j == a - 1 ? 0 : j + 1][k], dp[i][j][k]);
                        add(dp[i + 1][j][k == b - 1 ? 0 : k + 1], dp[i][j][k]);
                    }
                }
            }
            for(int cz = 0; cz <= n; cz += c) {
                add(ans, 1LL * C(n, cz) * dp[n - cz][0][0] % MOD);
            }
        }
        cout << ans << "\n";
    };
    work1();
    work2();
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
