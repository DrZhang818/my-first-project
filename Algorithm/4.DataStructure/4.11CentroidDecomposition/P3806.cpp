#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 10000000;

int T[N + 1];
int timer = 0;

void solve() {  
    int n, m;
    cin >> n >> m;
    auto adj = vector<vector<pair<int,int>>>(n + 1);

    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<int> query(m + 1);
    vector<bool> ans(m + 1);
    int mx = 0;
    for(int i = 1; i <= m; i++) {
        cin >> query[i];
        mx = max(mx, query[i]);
    }

    vector<int> sz(n + 1);
    vector<bool> vis(n + 1);

    auto get_sz = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(auto [v, w] : adj[u]) {
            if(v == fa || vis[v]) continue;
            self(v, u);
            sz[u] += sz[v];
        }
    };

    auto get_root = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(auto [v, w] : adj[u]) {
            if(v == fa || vis[v]) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    auto dfs = [&](this auto&& self, int u) -> void {
        get_sz(u, 0);
        u = get_root(u, 0, sz[u]);
        vis[u] = true;

        ++timer;
        if(T[0] != timer) {
            T[0] = timer;
        }

        for(auto [v, w] : adj[u]) {
            if(vis[v]) continue;

            vector<int> dist;
            auto get_dist = [&](this auto&& self, int x, int fa, int d) -> void {
                if(d > mx) return;
                dist.push_back(d);
                for(auto [y, c] : adj[x]) {
                    if(y == fa || vis[y]) continue;
                    self(y, x, d + c);
                }
            };
            get_dist(v, u, w);

            for(int d : dist) {
                for(int i = 1; i <= m; i++) {
                    if(ans[i]) continue;
                    if(query[i] - d < 0) continue;
                    if(T[query[i] - d] == timer) {
                        ans[i] = true;
                    }
                }
            }

            for(int d : dist) {
                T[d] = timer;
            }
        }

        for(auto [v, w] : adj[u]) {
            if(!vis[v]) {
                self(v);
            }
        }
    };  
    dfs(1);

    for(int i = 1; i <= m; i++) {
        if(ans[i]) {
            cout << "AYE\n";
        } else {
            cout << "NAY\n";
        }
    }
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
