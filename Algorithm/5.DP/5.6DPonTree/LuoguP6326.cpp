#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, S;
    cin >> n >> S;

    vector<int> w(n + 1), c(n + 1), d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> nums(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = d[i] - 1;
        int cur = 1;
        while(x >= cur) {
            nums[i].push_back(cur);
            x -= cur;
            cur <<= 1;
        }
        if(x > 0) nums[i].push_back(x);
    }

    vector<bool> vis(n + 1);
    vector<int> sz(n + 1);
    vector<int> in(n + 1), out(n + 1), seq(n + 1);

    auto calcSize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(int v : adj[u]) {
            if(vis[v] || v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
        }
    };

    auto getRoot = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(int v : adj[u]) {
            if(vis[v] || v == fa) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    auto getDfn = [&](int u) -> int {
        int timer = 1;
        [&](this auto&& self, int u, int fa) -> void {
            seq[timer] = u;
            in[u] = timer++;
            for(int v : adj[u]) {
                if(vis[v] || v == fa) continue;
                self(v, u);
            }
            out[u] = timer;
        }(u, 0);
        return timer - 1;
    };

    i64 ans = 0;
    auto dfs = [&](this auto&& self, int u) -> void {
        calcSize(u, 0);
        u = getRoot(u, 0, sz[u]);
        vis[u] = true;

        int m = getDfn(u);
        vector<vector<i64>> dp(m + 2, vector<i64>(S + 1));

        for(int i = m; i >= 1; i--) {
            int x = seq[i];

            for(int j = S; j >= c[x]; j--) {
                dp[i][j] = dp[i + 1][j - c[x]] + w[x];
            }

            for(int cnt : nums[x]) {
                for(int j = S; j >= c[x] * cnt; j--) {
                    dp[i][j] = max(dp[i][j], dp[i][j - c[x] * cnt] + w[x] * cnt);
                }
            }
            
            for(int j = S; j >= 0; j--) {
                dp[i][j] = max(dp[i][j], dp[out[x]][j]);
            }
        }

        ans = max(ans, dp[1][S]);

        for(int v : adj[u]) {
            if(!vis[v]) self(v);
        }
    };
    dfs(1);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}