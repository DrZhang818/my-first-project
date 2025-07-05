#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 1E9 + 7;
ll fast_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
const ll inv_2 = fast_pow(2, MOD - 2);
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }    
    // vector<ll> fac(n + 1);
    // vector<ll> inv_fac(n + 1);
    vector<ll> pow2(n + 1);
    pow2[0] = 1;
    for(int i = 1; i <= n; i++) {
        pow2[i] = pow2[i - 1] * 2 % MOD;
    }
    // const ll mi = pow2[n];
    // const ll inv_mi = fast_pow(mi, MOD - 2);
    // for(int i = 1; i <= n; i++) {
    //     fac[i] = fac[i - 1] * i % MOD;
    //     inv_fac[i] = fast_pow(fac[i], MOD - 2);
    // }
    // vector<ll> dp(n + 1);
    // for(int i = 0; i <= n; i++) {
    //     dp[i] = fac[n] * inv_mi % MOD * inv_fac[i] % MOD * inv_fac[n - i] % MOD * i % MOD;
    // }
    vector<ll> sz(n + 1, 1);
    ll ans = 0;
    auto dfs = [&](auto &&self, int u, int fa) -> ll {
        ll res = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            ll p = self(self, v, u);
            if(sz[v] != 1) {
                res = (res + inv_2 * (2 * p + 1) % MOD) % MOD;
            }
            sz[u] += sz[v];
        }
        ll cur = sz[u] - 1;
        ll rem = n - sz[u] + 1;
        cerr << u << " " << fa << " " << rem << " " << res << "\n";
        ans = (ans + fast_pow(pow2[rem], MOD - 2) * res % MOD) % MOD;
        return res;
    };
    dfs(dfs, 1, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
