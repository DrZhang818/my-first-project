#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

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
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    int rootedParent(int u, int v) {
        swap(u, v);
        if(u == v) {
            return u;
        }
        if(!isAncester(u, v)) {
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
        if(!isAncester(v, u)) {
            return siz[v];
        }
        return n - 1 - siz[rootedParent(u, v)];
    }
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
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
    auto &in = tr.in;
    vector<int> to(n + 1);
    vector<bool> tag(n + 1), vis(n + 1);
    int q;
    cin >> q;
    while(q--) {
        int k;
        cin >> k;
        vector<int> vex(k + 1);
        for(int i = 1; i <= k; i++) {
            cin >> vex[i];
            vis[vex[i]] = true;
        }
        bool ok = true;
        for(int i = 1; i <= k; i++) {
            if(vis[tr.parent[vex[i]]]) {
                ok = false;
                break;
            }
        }
        if(!ok) {
            cout << -1 << "\n";
            for(int i = 1; i <= k; i++) {
                vis[vex[i]] = false;
            }
            continue;
        } 
        auto tmp = vex;
        sort(vex.begin() + 1, vex.end(),
            [&](auto x, auto y) {
                return in[x] < in[y];
            });
        for(int i = 1; i < k; i++) {
            int u = vex[i], v = vex[i + 1];
            int lca = tr.lca(u, v);
            vex.push_back(lca);
        }
        sort(vex.begin() + 1, vex.end(),
            [&](auto x, auto y) {
                return in[x] < in[y];
            });
        vex.erase(unique(vex.begin() + 1, vex.end()), vex.end());
        int m = vex.size() - 1;
        for(int i = 1; i <= m; i++) {
            to[vex[i]] = i;
        }
        for(int i = 1; i <= k; i++) {
            tag[to[tmp[i]]] = true;
        }
        vector g(m + 1, vector<int> {});
        for(int i = 1; i < m; i++) {
            int lca = to[tr.lca(vex[i], vex[i + 1])];
            g[lca].push_back(i + 1);
            g[i + 1].push_back(lca);
        }
        int ans = 0;
        auto dfs = [&](this auto && self, int u, int fa) -> int {
            int s = tag[u];
            int c = 0;
            for(int v : g[u]) {
                if(v == fa) continue;
                c += self(v, u);
            }
            if(s == 0) {
                if(c <= 1) {
                    return c;
                } else {
                    ans += 1;
                    return 0;
                }
            } else {
                ans += c;
                return 1;
            }
        };  
        dfs(1, 0);
        cout << ans << "\n";
        for(int i = 1; i <= k; i++) {
            tag[to[tmp[i]]] = false;
            vis[tmp[i]] = false;
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
