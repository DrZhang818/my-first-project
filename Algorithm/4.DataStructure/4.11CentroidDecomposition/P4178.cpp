#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

struct Edge {
    int v, w;
};

void solve() {
    int n;
    cin >> n;

    vector<vector<Edge>> adj(n + 1);

    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    int k;
    cin >> k;

    vector<int> sz(n + 1);
    vector<bool> vis(n + 1);

    auto getSize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(auto [v, _] : adj[u]) {
            if(v == fa || vis[v]) continue;
            self(v, u);
            sz[u] += sz[v];
        }
    };

    auto getRoot = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(auto [v, _] : adj[u]) {
            if(v == fa || vis[v]) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    auto calc = [&](int u, int fa, int d) -> i64 {
        vector<int> cur;
        [&](this auto&& self, int u, int fa, int d) -> void {
            if(d > k) return;
            cur.push_back(d);
            for(auto [v, w] : adj[u]) {
                if(v == fa || vis[v]) continue;
                self(v, u, d + w);
            }
        }(u, fa, d);
        sort(cur.begin(), cur.end());
        int l = 0, r = cur.size() - 1;
        i64 res = 0;
        while(l < r) {
            if(cur[l] + cur[r] <= k) {
                res += r - l;
                l++;
            } else {
                r--;
            }
        }
        return res;
    };

    i64 ans = 0;
    auto dfs = [&](this auto&& self, int u) -> void {
        getSize(u, 0);
        u = getRoot(u, 0, sz[u]);
        vis[u] = true;

        ans += calc(u, 0, 0);
        for(auto [v, w] : adj[u]) {
            if(!vis[v]) {
                ans -= calc(v, u, w);
                self(v);
            }
        }
    };
    dfs(1);

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
