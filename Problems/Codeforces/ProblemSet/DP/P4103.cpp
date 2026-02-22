#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

// [in[u], out[u] - 1] 是以u为根的子树的dfs序区间
struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in;
    vector<vector<int>> adj;
    int cur;

    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        cur = 1;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 1) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = 0;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if(parent[u]) {
            adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for(auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        for(auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
    }
    int lca(int u, int v) {
        while(top[u] != top[v]) {
            if(dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};

void solve() {  
    int n;
    cin >> n;

    HLD tr(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tr.addEdge(u, v);
    }
    tr.work();

    auto& in = tr.in;

    vector<vector<int>> vt(n + 1);
    vector<bool> tag(n + 1);
    vector<int> siz(n + 1);
    vector<int> mn(n + 1), mx(n + 1);
    vector<i64> dp(n + 1);

    int q;
    cin >> q;
    while(q--) {
        int k;
        cin >> k;
        
        vector<int> Q(k + 1);
        vector<int> nodes;
        nodes.reserve(k);

        for(int i = 1; i <= k; i++) {
            cin >> Q[i];
            nodes.push_back(Q[i]);
            tag[Q[i]] = true;
        }

        auto cmp = [&](auto x, auto y) { return in[x] < in[y]; };
        sort(nodes.begin(), nodes.end(), cmp);

        int sz = nodes.size();
        for(int i = 0; i < sz - 1; i++) {
            nodes.push_back(tr.lca(nodes[i], nodes[i + 1]));
        }

        sort(nodes.begin(), nodes.end(), cmp);

        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        sz = nodes.size();

        for(int i = 0; i < sz - 1; i++) {
            int lca = tr.lca(nodes[i], nodes[i + 1]);
            vt[lca].push_back(nodes[i + 1]);
            vt[nodes[i + 1]].push_back(lca);
        }

        i64 sum = 0;
        int ans_mn = inf, ans_mx = -inf;

        auto dfs = [&](this auto&& self, int u, int fa) -> void {
            if(tag[u]) {
                siz[u] = 1;
                mn[u] = mx[u] = 0;
            } else {
                mn[u] = inf;
                mx[u] = -inf;
            }

            for(int v : vt[u]) {
                if(v == fa) continue;
                self(v, u);
                int d = tr.dist(u, v);
                sum += dp[u] * siz[v] + dp[v] * siz[u] + 1LL * d * siz[u] * siz[v];
                dp[u] += dp[v] + 1LL * siz[v] * d;
                siz[u] += siz[v];
                ans_mn = min(ans_mn, mn[u] + mn[v] + d);
                ans_mx = max(ans_mx, mx[u] + mx[v] + d);
                mn[u] = min(mn[u], mn[v] + d);
                mx[u] = max(mx[u], mx[v] + d);
            }

        };
        dfs(nodes[0], 0);

        cout << sum << " " << ans_mn << " " << ans_mx << "\n";

        for(int u : nodes) {
            vt[u].clear();
            tag[u] = false;
            siz[u] = 0;
            mn[u] = mx[u] = 0;   
            dp[u] = 0;
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
