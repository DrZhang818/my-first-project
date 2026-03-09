#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 10000000;

vector<int> minp, primes;

auto init = []() {
    minp.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }

    return 0;
}();

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

struct Query {
    int u, v, p, e, id;
    friend bool operator<(const Query& a, const Query& b) {
        if(a.p != b.p) {
            return a.p < b.p;
        }
        return a.e < b.e;
    }
};

struct Node {
    int u, p, e;
    friend bool operator<(const Node& a, const Node& b) {
        if(a.p != b.p) {
            return a.p < b.p;
        } 
        return a.e < b.e;
    }
};

inline int lowbit(int o) { return o & -o; }

constexpr int MOD = 1000000007;

void add_mod(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int power(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) {
            res = 1LL * res * a % MOD;
        }
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

struct FenwickTree {
    int n;
    vector<int> tr;
    int timer;
    vector<int> time;
    int tag;
    FenwickTree(int n) : n(n), tr(n), timer(0), time(n) {}

    void reset() {
        timer++;
    }

    void add(int o, int x) {
        for(; o < n; o += lowbit(o)) {
            if(time[o] != timer) {
                time[o] = timer;
                tr[o] = 0;
            }
            add_mod(tr[o], x);
        }
    }

    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            if(time[o] != timer) {
                time[o] = timer;
                tr[o] = 0;
            }
            add_mod(res, tr[o]);
        }
        return res;
    }

    int range_query(int l, int r) {
        int res_r = query(r);
        int res_l = query(l - 1);
        add_mod(res_r, MOD - res_l);
        return res_r;
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
    auto& out = tr.out;
    auto& fa = tr.parent;

    vector<Node> A;
    A.reserve(n);

    for(int i = 1; i <= n; i++) {
        int x; 
        cin >> x;
        while(x > 1) {
            int p = minp[x], e = 0;
            while(minp[x] == p) {
                e++;
                x /= p;
            }
            A.emplace_back(i, p, e);
        }
    }

    int q;
    cin >> q;

    vector<Query> Q;
    Q.reserve(q);

    for(int i = 1; i <= q; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        while(x > 1) {
            int p = minp[x], e = 0;
            while(minp[x] == p) {
                e++;
                x /= p;
            }
            Q.emplace_back(u, v, p, e, i);
        }
    }

    sort(A.begin(), A.end());
    sort(Q.begin(), Q.end());

    vector<int> ans(q + 1, 1);

    FenwickTree fen1(n + 2), fen2(n + 2);

    int al = 0, ar = 0;

    for(int ql = 0, qr = 0; ql < Q.size(); ql = qr) {
        while(qr < Q.size() && Q[qr].p == Q[ql].p) {
            qr++;
        }

        int p = Q[ql].p;

        while(al < A.size() && A[al].p < p) {
            al++;
        }
        if(A[al].p != p) {
            continue;
        }
        ar = al;
        while(ar < A.size() && A[ar].p == p) {
            ar++;
        }

        fen1.reset();
        fen2.reset();

        for(int i = al; i < ar; i++) {
            fen2.add(in[A[i].u], 1);
            fen2.add(out[A[i].u], -1);
        }

        for(int i = ql, j = al; i < qr; i++) {
            auto [u, v, _, e, id] = Q[i];

            while(j < ar && A[j].e < e) {
                auto [o, _, ae] = A[j++];
                fen1.add(in[o], ae);
                fen1.add(out[o], -ae);
                fen2.add(in[o], -1);
                fen2.add(out[o], 1);
            }

            int lca = tr.lca(u, v);

            int sum = fen1.query(in[u]) + fen1.query(in[v]) - fen1.query(in[lca]) - fen1.query(in[fa[lca]]);
            sum += e * (fen2.query(in[u]) + fen2.query(in[v]) - fen2.query(in[lca]) - fen2.query(in[fa[lca]]));

            ans[id] = 1LL * ans[id] * power(p, sum) % MOD;
        }
    }

    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
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
