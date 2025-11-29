#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
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


void solve() {
    int n;
    cin >> n;
    vector adj(n + 1, vector<int>{});
    for(int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        adj[f].push_back(i);
    }
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]++;
    }
    vector<int> seq;
    vector dp(n + 2, vector<int>(n + 2)), sz(n + 2, vector<int>(n + 2));
    dp[0][n + 1] = 1;

    vector<int> rk{0, n + 1};

    auto dfs = [&](this auto &&self, int u) -> bool {
        if(a[u] >= rk.size()) {
            return false;
        }
        int pre = rk[a[u] - 1], suf = rk[a[u]];
        rk.insert(rk.begin() + a[u], u);
        dp[pre][u] = dp[u][suf] = 1;
        auto t = rk;
        for(int v : adj[u]) {
            if(!self(v)) {
                return false;
            }
            rk = t;
        }
        dp[pre][suf] = 1LL * dp[pre][suf] * dp[pre][u] % MOD * dp[u][suf] % MOD * C(sz[pre][u] + sz[u][suf] + sz[pre][suf] + 1, sz[pre][suf]) % MOD;
        sz[pre][suf] += sz[pre][u] + sz[u][suf] + 1;        
        return true;
    };
    if(!dfs(1)) {
        cout << 0 << "\n";
        return;
    }
    cout << dp[0][n + 1] << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
