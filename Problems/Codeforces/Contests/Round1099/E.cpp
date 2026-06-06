#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

// [in[u], out[u] - 1] 是以u为根的子树的dfs序区间
struct HLD {
    int n;
    vector<int> siz, top, dep, parent, in, out, seq;
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
        out.resize(n);
        seq.resize(n);
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
        seq[in[u]] = u;
        for(auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
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
    int jump(int u, int k) {
        if(dep[u] < k) {
            return 0;
        }
        int d = dep[u] - k;
        while(dep[top[u]] > d) {
            u = parent[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
    bool isAncestor(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    int rootedParent(int u, int v) {
        swap(u, v);
        if(u == v) {
            return u;
        }
        if(!isAncestor(u, v)) {
            return parent[u];
        }
        auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    int rootedSize(int u, int v) {
        if(u == v) {
            return n - 1;
        }
        if(!isAncestor(v, u)) {
            return siz[v];
        }
        return n - 1 - siz[rootedParent(u, v)];
    }
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};


void solve() {
    int n, d;
    cin >> n >> d;

    HLD tr(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tr.addEdge(u, v);
    }
    tr.work();
    vector<vector<int>> down(n + 1, vector<int>(n + 1)), out(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        down[i][0] = 1;
    }

    for(int u = 1; u <= n; u++) {
        for(int v = 1; v <= n; v++) {
            if(v == u) continue;
            int dis = tr.dist(u, v);
            if(tr.isAncestor(u, v)) {
                down[u][dis]++;
            } else {
                out[u][dis]++;
            }
        }
    }

    int D = d - 1;
    i64 ans = 0;
    i64 cntDown = 0;
    i64 cntOut = 0;

    for(int u = 1; u <= n; u++) {
        for(int v = u + 1; v <= n; v++) {
            int dis = tr.dist(u, v);
            if(dis > D) continue;
            if(dis == D) {
                ans += D - 1;
                continue;
            }

            int w = tr.lca(u, v);
            if(w == u || w == v) continue;
            
            int fu = tr.jump(u, tr.dist(u, w) - 1);
            int fv = tr.jump(v, tr.dist(v, w) - 1);

            int rem = D - dis;
                
            cntDown += down[w][rem] - down[fu][rem - 1] - down[fv][rem - 1];
            cntOut += out[w][rem];
        }
    }

    ans += cntDown / 3 + cntOut;

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