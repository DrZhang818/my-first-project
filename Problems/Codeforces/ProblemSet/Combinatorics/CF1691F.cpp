#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 2E5;
constexpr int MOD = 1E9 + 7;

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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sz(n + 1);

    int ans = 0;

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        int sum = 0;
        sz[u] = 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
            add(sum, binom(sz[v], k));
        } 
        add(sum, binom(n - sz[u], k));

        add(ans, 1LL * n * (binom(n, k) + MOD - sum) % MOD);
        for(int v : adj[u]) {
            int t = v == fa ? n - sz[u] : sz[v];
            int cur = sum;
            add(cur, MOD - binom(t, k));

            add(ans, 1LL * t * (n - t) % MOD * (binom(n - t, k) + MOD - cur) % MOD);
        }
    };
    dfs(1, 0);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}