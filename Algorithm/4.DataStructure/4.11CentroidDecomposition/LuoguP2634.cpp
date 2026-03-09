#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    auto adj = vector<vector<pair<int,int>>>(n + 1);

    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w % 3);
        adj[v].emplace_back(u, w % 3);
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

    i64 ans = 0;

    auto dfs = [&](this auto&& self, int u) -> void {
        get_sz(u, 0);
        u = get_root(u, 0, sz[u]);
        vis[u] = true;

        array<int, 3> cnt {};
        cnt[0] = 1;

        for(auto [v, w] : adj[u]) {
            if(vis[v]) continue;

            vector<int> dist;
            auto get_dist = [&](this auto&& self, int x, int fa, int d) -> void {
                dist.push_back(d);
                for(auto [y, c] : adj[x]) {
                    if(y == fa || vis[y]) continue;
                    self(y, x, (d + c) % 3);
                }
            };
            get_dist(v, u, w);

            for(int d : dist) {
                ans += cnt[(3 - d) % 3];
            }

            for(int d : dist) { 
                cnt[d]++;
            }
        }

        for(auto [v, w] : adj[u]) {
            if(!vis[v]) {
                self(v);
            }
        }
    };
    dfs(1);

    ans = ans * 2 + n;
    i64 sum = 1LL * n * n;
    auto g = gcd(ans, sum);

    cout << ans / g << "/" << sum / g << "\n";

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
