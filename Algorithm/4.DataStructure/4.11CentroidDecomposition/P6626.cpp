#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> sz(n + 1);
    vector<bool> vis(n + 1);

    auto getSize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(int v : adj[u]) {
            if(v != fa && !vis[v]) {
                self(v, u);
                sz[u] += sz[v];
            }
        }
    };

    auto getRoot = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(int v : adj[u]) {
            if(v == fa || vis[v]) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    vector<vector<pair<int,int>>> Q(n + 1);
    vector<int> ans(q);
    vector<int> cnt(n + 1);
    int timer = 0;
    vector<int> T(n + 1);

    auto calc = [&](this auto&& self, int u, int fa, int d, bool is_add) -> void {
        ++timer;
        [&](this auto&& dfs, int u, int fa, int d) -> void {
            if(T[d] != timer) {
                T[d] = timer;
                cnt[d] = 1;
            } else {
                cnt[d]++;
            }
            for(int v : adj[u]) {
                if(v == fa || vis[v]) continue;
                dfs(v, u, d + 1);
            }
        } (u, fa, d);

        [&](this auto&& dfs, int u, int fa, int d) -> void {
            for(auto [k, id] : Q[u]) {
                if(d > k) continue;
                if(T[k - d] != timer) continue;
                if(is_add) ans[id] += cnt[k - d];
                else       ans[id] -= cnt[k - d];
            }
            for(int v : adj[u]) {
                if(v == fa || vis[v]) continue;
                dfs(v, u, d + 1);
            }
        } (u, fa, d);
    };

    auto dfs = [&](this auto&& self, int u) -> void {
        getSize(u, 0);
        u = getRoot(u, 0, sz[u]);
        vis[u] = true;

        calc(u, 0, 0, true);
        for(int v : adj[u]) {
            if(!vis[v]) {
                calc(v, u, 1, false);
            }
        }

        for(int v : adj[u]) {
            if(!vis[v]) {
                self(v);
            }
        }
    };

    for(int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        Q[x].emplace_back(k, i);
    }

    dfs(1);

    for(int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
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
