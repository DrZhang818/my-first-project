#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
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

class FenwickTree {
private:
    vector<i64> tree;
    vector<int> time;
    int n;
public:
    int timer;
    FenwickTree(int x) {
        tree.resize(x + 1);
        time.resize(x + 1);
        n = x;
        timer = 0;
    }
    void add(int i, int x) {
        while(i <= n) {
            if(time[i] != timer) {
                time[i] = timer;
                tree[i] = 0;
            }
            tree[i] += x;
            i += i & -i;
        }
    }
    i64 query(int i) {
        i64 res = 0;
        while(i > 0) {
            if(time[i] != timer) {
                time[i] = timer;
                tree[i] = 0;
            }
            res += tree[i];
            i -= i & -i;
        }
        return res;
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

    FenwickTree fen(n + 1), sum(n + 1);

    auto& in = tr.in;
    auto& out = tr.out;
    auto& seq = tr.seq;
    auto& adj = tr.adj;

    auto dfs = [&](auto&& self, int u) -> void {
        for(int i = 1; i < adj[u].size(); i++) {
            int v = adj[u][i];
            self(self, v);
            fen.timer++;
        }
        i64 cnt = 0;
        if(!adj[u].empty()) {
            self(self, adj[u][0]);
            cnt = fen.query(u - 1);
            sum.add(1, cnt);
            sum.add(in[adj[u][0]], -cnt);
            sum.add(out[adj[u][0]], cnt);
        }
        fen.add(u, 1);
        for(int i = 1; i < adj[u].size(); i++) {
            int v = adj[u][i];
            i64 cur = 0;
            for(int j = in[v]; j < out[v]; j++) {
                fen.add(seq[j], 1);
                if(seq[j] < u) {
                    cur++;
                }
            }
            sum.add(1, cur);
            sum.add(in[v], -cur);
            sum.add(out[v], cur);
            cnt += cur;
        }
        i64 rem = u - 1 - cnt;
        sum.add(in[u], rem);
        sum.add(out[u], -rem);
    };
    dfs(dfs, 1);

    for(int i = 1; i <= n; i++) {
        cout << sum.query(in[i]) << " \n"[i == n];
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
