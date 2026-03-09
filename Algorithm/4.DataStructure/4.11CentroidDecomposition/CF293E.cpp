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
    i64 w;
    int len;

    friend bool operator<(const Info& a, const Info& b) {
        return a.w < b.w;
    }
};

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<int> tr;
    int timer;
    vector<int> T;
    FenwickTree(int n) : n(n), tr(n), timer(0), T(n) {}

    void reset() {
        timer++;
    }

    void add(int o, int x) {
        o++;
        for(; o < n; o += lowbit(o)) {
            if(T[o] != timer) {
                T[o] = timer;
                tr[o] = x;
            } else {
                tr[o] += x;
            }
        }
    }

    int query(int o) {
        o++;
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            if(T[o] != timer) continue;
            res += tr[o];
        }
        return res;
    }
};

void solve() {
    int n, lim_L, lim_W;
    cin >> n >> lim_L >> lim_W;

    vector<vector<Edge>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int p, w;
        cin >> p >> w;
        adj[p].emplace_back(i + 1, w);
        adj[i + 1].emplace_back(p, w);
    }

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

    FenwickTree fen(n + 5);

    auto calc = [&](this auto&& self, int u, int fa, i64 d, int len) -> i64 {
        fen.reset();

        vector<Info> cur;

        [&](this auto&& self, int u, int fa, i64 d, int len) -> void {
            if(d > lim_W || len > lim_L) return;
            cur.emplace_back(d, len);
            fen.add(len, 1);
            for(auto [v, w] : adj[u]) {
                if(v == fa || vis[v]) continue;
                self(v, u, d + w, len + 1);
            }
        }(u, fa, d, len);

        sort(cur.begin(), cur.end());        

        i64 res = 0;
        int l = 0, r = cur.size() - 1;
        while(l < r) {
            if(cur[l].w + cur[r].w <= lim_W) {
                fen.add(cur[l].len, -1);
                res += fen.query(lim_L - cur[l].len);
                l++;
            } else {
                fen.add(cur[r].len, -1);
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

        ans += calc(u, 0, 0, 0);
        for(auto [v, w] : adj[u]) {
            if(!vis[v]) {
                ans -= calc(v, u, w, 1);
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
