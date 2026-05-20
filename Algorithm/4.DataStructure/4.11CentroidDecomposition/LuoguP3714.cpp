#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr i64 inf = 1E18;

struct SegmentTree {
    int n;
    vector<i64> tr;
    vector<int> tmp;

    SegmentTree(int n) : n(n), tr(n << 1, -inf) {}

    void update(int o, i64 val) {
        int leaf = o;
        o += n;
        if(val <= tr[o]) return;
        if(tr[o] == -inf) tmp.push_back(leaf);
        tr[o] = val;
        for(o >>= 1; o; o >>= 1) {
            tr[o] = max(tr[o << 1], tr[o << 1 | 1]);
        }
    } 

    i64 query(int l, int r) {
        if(l > r) return -inf;
        i64 res = -inf;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = max(res, tr[l++]);
            if(r & 1) res = max(res, tr[--r]);
        }
        return res;
    }

    void rollback() {
        for(int o : tmp) {
            o += n;
            tr[o] = -inf;
            for(o >>= 1; o; o >>= 1) {
                tr[o] = max(tr[o << 1], tr[o << 1 | 1]);
            }
        }
        tmp.clear();
    }
};

void solve() {
    int n, m, l, r;
    cin >> n >> m >> l >> r;

    vector<int> w(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> w[i];
    }

    vector<vector<pair<int, int>>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, col;
        cin >> u >> v >> col;
        adj[u].emplace_back(v, col);
        adj[v].emplace_back(u, col);
    }

    vector<int> vis(n + 1);
    vector<int> sz(n + 1);
    SegmentTree seg1(r + 1), seg2(r + 1);

    auto resize = [&](this auto&& self, int u, int fa) -> void {
        sz[u] = 1;
        for(auto [v, _] : adj[u]) {
            if(vis[v] || v == fa) continue;
            self(v, u);
            sz[u] += sz[v];
        }
    };

    auto get = [&](this auto&& self, int u, int fa, int tot) -> int {
        for(auto [v, _] : adj[u]) {
            if(vis[v] || v == fa) continue;
            if(sz[v] > tot / 2) return self(v, u, tot);
        }
        return u;
    };

    i64 ans = -inf;

    auto dfs = [&](this auto&& self, int u) -> void {
        resize(u, 0);
        u = get(u, 0, sz[u]);
        vis[u] = true;

        seg1.update(0, 0);

        sort(adj[u].begin(), adj[u].end(), 
            [&](auto& x, auto& y) {
                return x.second < y.second;
            });

        auto calc = [&](this auto&& calc, auto& seg, int u, int fa, int sum, int cnt, int las) -> void {
            if(cnt > r) return ;
            ans = max(ans, sum + seg.query(max(0, l - cnt), r - cnt));
            for(auto [v, col] : adj[u]) {
                if(vis[v] || v == fa) continue;
                if(col == las) {
                    calc(seg, v, u, sum, cnt + 1, col);
                } else {
                    calc(seg, v, u, sum + w[col], cnt + 1, col);
                }
            }
        };

        auto insert = [&](this auto&& insert, int u, int fa, int sum, int cnt, int las) -> void {
            if(cnt > r) return;
            seg1.update(cnt, sum);
            seg2.update(cnt, sum);
            for(auto [v, col] : adj[u]) {
                if(vis[v] || v == fa) continue;
                if(col == las) {
                    insert(v, u, sum, cnt + 1, col);
                } else {
                    insert(v, u, sum + w[col], cnt + 1, col);
                }
            }
        };

        int tot = adj[u].size();
        for(int L = 0, R = 0; L < tot; L = R) {
            int col = adj[u][L].second;
            while(R < tot && adj[u][R].second == col) R++;
            for(int i = L; i < R; i++) {
                auto [v, _] = adj[u][i];
                if(vis[v]) continue;
                calc(seg1, v, u, w[col], 1, col);
            }
            for(int i = L; i < R; i++) {
                auto [v, _] = adj[u][i];
                if(vis[v]) continue;
                calc(seg2, v, u, 0, 1, col);
                insert(v, u, w[col], 1, col);
            }
            seg2.rollback();
        }
        seg1.rollback();

        for(auto [v, _] : adj[u]) {
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
    while(t--) {
        solve();
    }
    return 0;
}