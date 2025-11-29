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
            return n;
        }
        if(!isAncester(u, v)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1);
    HLD tr(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
        int fa;
        cin >> fa;
        if(fa) {
            tr.addEdge(i, fa);
        }
    }
    tr.work();
    vector<int> cnt1(n + 1), cnt2(n + 1);
    int ans = 0;
    auto &adj = tr.adj;
    auto &siz = tr.siz;
    auto add = [&](auto &&self, int u) -> void {
        cnt2[cnt1[c[u]]]--;
        cnt2[++cnt1[c[u]]]++;
        for(int v : adj[u]) {
            self(self, v);
        }
    };
    auto del = [&](auto &&self, int u) -> void {
        cnt2[cnt1[c[u]]] = 0;
        cnt1[c[u]] = 0;
        for(int v : adj[u]) {
            self(self, v);
        }
    };
    auto dfs = [&](auto &&self, int u, bool keep) -> void {
        for(int i = 1; i < adj[u].size(); i++) {
            self(self, adj[u][i], 0);
        }
        if(!adj[u].empty()) {
            self(self, adj[u][0], 1);
        }
        cnt2[cnt1[c[u]]]--;
        cnt2[++cnt1[c[u]]]++;
        for(int i = 1; i < adj[u].size(); i++) {
            add(add, adj[u][i]);
        }
        if(cnt1[c[u]] * cnt2[cnt1[c[u]]] == siz[u]) {
            ans++;
        }
        if(keep == 0) {
            del(del, u);
        }
    };
    dfs(dfs, 1, 1);
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
