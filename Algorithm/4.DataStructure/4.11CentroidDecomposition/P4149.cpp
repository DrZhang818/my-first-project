#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

struct Edge {
    int v, w;
};

struct Info {
    int w, cnt;
};

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<Edge>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u++;
        v++;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    if(k == 0) {
        cout << 0 << "\n";
        return;
    }

    vector<int> vis(n + 1);
    vector<int> sz(n + 1);

    auto getSize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(auto [v, w] : adj[u]) {
            if(v == fa || vis[v]) continue;
            self(v, u);
            sz[u] += sz[v];
        }
    };

    auto getRoot = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(auto [v, w] : adj[u]) {
            if(v == fa || vis[v]) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    vector<int> dp(k + 1, inf);
    vector<int> T(k + 1);
    int timer = 0;
    int ans = inf;

    vector<Info> cur;

    auto dfs = [&](this auto&& self, int u) -> void {
        getSize(u, 0);
        u = getRoot(u, 0, sz[u]);
        vis[u] = true;
        timer++;
        dp[0] = 0;
        T[0] = timer;

        for(auto [v, w] : adj[u]) {
            if(vis[v] || w > k) continue;
            cur.clear();

            [&](this auto&& self, int x, int fa, int d, int c) -> void {
                if(d <= k) {
                    cur.emplace_back(d, c);
                }
                for(auto [y, w2] : adj[x]) {
                    if(y == fa || vis[y]) continue;
                    if(d + w2 > k) continue;
                    self(y, x, d + w2, c + 1);
                }
            }(v, u, w, 1);

            for(auto [d, c] : cur) {
                if(T[k - d] == timer) {
                    ans = min(ans, c + dp[k - d]);
                }
            }

            for(auto [d, c] : cur) {
                if(T[d] != timer) {
                    T[d] = timer;
                    dp[d] = c;
                } else {
                    dp[d] = min(dp[d], c);
                }
            }
        }

        for(auto [v, w] : adj[u]) {
            if(!vis[v]) {
                self(v);
            }
        }
    };
    dfs(1);
    if(ans == inf) {
        ans = -1;
    }
    cout << ans << "\n";
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
