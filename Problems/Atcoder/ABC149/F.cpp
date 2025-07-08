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

void solve() {
    int n;
    cin >> n;
    vector<ll> pow_2(n + 1), inv_2(n + 1);
    pow_2[0] = inv_2[0] = 1;
    for(int i = 1; i <= n; i++) {
        pow_2[i] = pow_2[i - 1] * 2 % MOD;
        inv_2[i] = fast_pow(pow_2[i], MOD - 2);
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n + 1, 1); 
    ll ans = 0;
    const ll sum = n - 1;
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        ll cur = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            cur = (cur + (1 - inv_2[sz[v]] + MOD) % MOD * inv_2[sum - sz[v]] % MOD) % MOD;
        }
        cur = (cur + (1 - inv_2[n - sz[u]]) * inv_2[sum - n + sz[u]]) % MOD;
        cur = (cur + inv_2[sum]) % MOD;
        ans = (ans + (1 - cur + MOD) * inv_2[1]) % MOD;
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
