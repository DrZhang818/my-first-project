#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;
constexpr int N = 5000;

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

int inv_binom(int n, int r) {
    assert(r >= 0 && n >= r);
    return 1LL * ifac[n] * fac[r] % MOD * fac[n - r] % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int v = 2; v <= n; v++) {
        int u;
        cin >> u;
        adj[u].push_back(v);
    }

    vector<int> sz(n + 1), w(n + 1);
    auto dfs = [&](auto&& self, int u) -> void {
        sz[u] = 1;
        w[u] = 1;
        for(int v : adj[u]) {
            self(self, v);
            sz[u] += sz[v];
            w[u] = 1LL * w[u] * w[v] % MOD * binom(sz[u] - 1, sz[v]) % MOD;
        }
    };
    dfs(dfs, 1);

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    dp[1][1] = w[1];

    auto dfs2 = [&](auto&& self, int u) -> void {
        for(int v : adj[u]) {
            int sum = 0, s = sz[v];
            for(int k = 2; k <= n - s + 1; k++) {
                add(sum, 1LL * dp[u][k - 1] * inv_binom(n - k + 1, s) % MOD);
                dp[v][k] = 1LL * sum * binom(n - k, s - 1) % MOD;
            }
            self(self, v);            
        }
    };
    dfs2(dfs2, 1);

    for(int u = 1; u <= n; u++) {
        cout << dp[u][u] << " \n"[u == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}