#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> points(m + 1);
    vector<int> col(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> col[i];
        points[col[i]].push_back(i);
    }

    vector<bool> vis(n + 1);
    vector<int> vis_col(m + 1);
    vector<int> T(n + 1);
    vector<int> tag(n + 1);

    vector<int> sz(n + 1);
    vector<int> fa(n + 1);

    auto getSize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(int v : adj[u]) {
            if(!vis[v] && v != fa) {
                self(v, u);
                sz[u] += sz[v];
            }
        }
    };

    auto getRoot = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(int v : adj[u]) {
            if(vis[v] || v == fa) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    auto getFa = [&](this auto&& self, int u, int p, int rt) -> void {
        fa[u] = p;
        T[u] = rt;
        for(int v : adj[u]) {
            if(!vis[v] && v != p) {
                self(v, u, rt);
            }
        }
    };

    int ans = inf;

    auto dfs = [&](this auto&& self, int u) -> void {
        getSize(u, 0);
        u = getRoot(u, 0, sz[u]);
        vis[u] = true;
        getFa(u, 0, u);

        int cur = 0;
        queue<int> q;
        q.push(col[u]);
        vis_col[col[u]] = u;
        bool ok = true;
        while(!q.empty() && ok) {
            int c = q.front(); q.pop();
            for(int v : points[c]) {
                if(T[v] != u) {
                    cur = inf;
                    break;
                }
                int x = v;
                while(x && tag[x] != u) {
                    tag[x] = u;
                    if(vis_col[col[x]] != u) {
                        cur++;
                        vis_col[col[x]] = u;
                        q.push(col[x]);
                    }
                    x = fa[x];
                }
            }
        }
        ans = min(ans, cur);

        for(int v : adj[u]) {
            if(!vis[v]) {
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
