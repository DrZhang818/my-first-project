#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;


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

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    vector<int> fa(n + 1), top(n + 1), sz(n + 1), son(n + 1), dep(n + 1);
    for(int i = 2; i <= n; i++) {
        cin >> fa[i];
        adj[fa[i]].push_back(i);
    }
    auto dfs1 = [&](this auto &&self, int u) -> void {
        sz[u] = 1;
        dep[u] = dep[fa[u]] + 1;
        for(int v : adj[u]) {
            self(v);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]]) {
                son[u] = v;
            }
        }
    };
    dfs1(1);
    auto dfs2 = [&](this auto &&self, int u, int t) -> void {
        top[u] = t;
        if(!son[u]) {
            return;
        }
        self(son[u], t);
        for(int v : adj[u]) {
            if(v == fa[u] || v == son[u]) continue;
            self(v, v);
        }
    };
    dfs2(1, 1);
    auto LCA = [&](int u, int v) -> int {
        while(top[u] != top[v]) {
            if(dep[top[u]] < dep[top[v]]) {
                swap(u, v);
            }
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    };


    vector<int> f(n + 1), g(n + 1), sumf(n + 1), fo(n + 1);
    auto dfs = [&](this auto &&self, int u) -> void {
        f[u] = 1;
        for(int v : adj[u]) {
            self(v);
            f[u] = 1LL * f[u] * (1 + f[v]) % MOD;
        }
    };
    dfs(1);
    g[1] = f[1];
    auto work = [&](this auto &&self, int u) -> void {
        add(sumf[u], f[u]);
        int d = int(adj[u].size());
        if(d == 0) {
            return;
        }
        vector<int> pre(d), suf(d);
        pre[0] = (1 + fo[u]) % MOD;
        suf[d - 1] = 1;
        for(int i = 0; i < d - 1; i++) {
            int v = adj[u][i];
            pre[i + 1] = 1LL * pre[i] * (1 + f[v]) % MOD;
        }
        for(int i = d - 1; i > 0; i--) {
            int v = adj[u][i];
            suf[i - 1] = 1LL * suf[i] * (1 + f[v]) % MOD;
        }
        for(int i = 0; i < d; i++) {
            int v = adj[u][i];
            fo[v] = 1LL * pre[i] * suf[i] % MOD;
            g[v] = 1LL * f[v] * (1 + fo[v]) % MOD;
            sumf[v] = sumf[u];
            self(v);
        }
    };
    work(1);
    while(q--) {
        int u, v;
        cin >> u >> v;
        int l = LCA(u, v);
        int ans = 0;
        add(ans, sumf[u]);
        add(ans, sumf[v]);
        add(ans, MOD - 2LL * sumf[l] % MOD);
        add(ans, g[l]);
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
