#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

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
    vector<bool> tag(n + 2);
    HLD tr(n + 2);
    for(int i = 2; i <= n + 1; i++) {
        int fa;
        cin >> fa;
        fa++;
        tr.addEdge(i, fa);
        tag[i] = fa == 0;
    }
    tr.work(1);
    int q;
    cin >> q;
    vector<int> ans(q + 1);
    vector<vector<PII>> Q(n + 2);    
    for(int i = 1; i <= q; i++) {
        int u, k;
        cin >> u >> k;
        u++;
        int res = tr.jump(u, k);
        if(res <= 1) {
            ans[i] = 0;
        } else {
            Q[res].emplace_back(k, i);
        }
    }
    auto &dep = tr.dep;
    auto &adj = tr.adj;
    vector<int> cnt(n + 2);
    auto modify = [&](this auto &&self, int u, int d) -> void {
        cnt[dep[u]] += d;
        for(int v : adj[u]) {
            self(v, d);
        }
    };  
    auto dfs = [&](this auto &&self, int u, bool keep) -> void {
        for(int i = 1; i < adj[u].size(); i++) {
            self(adj[u][i], false);
        }
        if(adj[u].size()) self(adj[u][0], true);
        cnt[dep[u]]++;
        for(int i = 1; i < adj[u].size(); i++) {
            modify(adj[u][i], 1);
        }
        for(auto [k, id] : Q[u]) {
            ans[id] = cnt[dep[u] + k] - 1;
        }
        if(!keep) {
            modify(u, -1);
        }
    };
    dfs(1, 1);
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << " \n"[i == q];
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
