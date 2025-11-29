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

template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        auto build = [&](auto &&self, int o, int l, int r) {
            if(l == r) {
                info[o] = init_[l];
                return;
            }
            int m = l + r >> 1;
            self(self, o << 1, l, m);
            self(self, o << 1 | 1, m + 1, r);
            pull(o);
        };
        build(build, 1, 0, n - 1);
    }
    void pull(int o) {
        info[o] = info[o << 1] + info[o << 1 | 1];
    }
    void apply(int o, const Tag &v) {
        info[o].apply(v);
        tag[o].apply(v);
    }
    void push(int o) {
        apply(o << 1, tag[o]);
        apply(o << 1 | 1, tag[o]);
        tag[o] = Tag();
    }
    void modify(int o, int l, int r, int x, const Info &v) {
        if(l == r) {
            info[o] = v;
            return ;
        }
        int m = l + r >> 1;
        push(o);
        if(x <= m) modify(o << 1, l, m, x, v);
        else modify(o << 1 | 1, m + 1, r, x, v);
        pull(o);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n - 1, x, v);
    }
    Info rangeQuery(int o, int l, int r, int x, int y) {
        if(l > y || r < x) {
            return Info();
        }
        if(x <= l && r <= y) {
            return info[o];
        }
        int m = l + r >> 1;
        push(o);
        return rangeQuery(o << 1, l, m, x, y) + rangeQuery(o << 1 | 1, m + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
    void rangeApply(int o, int l, int r, int x, int y, const Tag &v) {
        if(l > y || r < x) {
            return ;
        }
        if(x <= l && r <= y) {
            apply(o, v);
            return;
        }
        int m = l + r >> 1;
        push(o);
        rangeApply(o << 1, l, m, x, y, v);
        rangeApply(o << 1 | 1, m + 1, r, x, y, v);
        pull(o);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n - 1, l, r, v);
    }
    template<class F> 
    int findFirst(int o, int l, int r, int x, int y, F &&pred) {
        if(l > y || r < x) {
            return -1;
        }
        if(x <= l && r <= y && !pred(info[o])) {
            return -1;
        }
        if(l == r) {
            return l;
        }
        int m = l + r >> 1;
        push(o);
        int res = findFirst(o << 1, l, m, x, y, pred);
        if(res == -1) {
            res = findFirst(o << 1 | 1, m + 1, r, x, y, pred);
        }
        return res;
    }
    template<class F> 
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n - 1, l, r, pred);
    }
    template<class F>
    int findLast(int o, int l, int r, int x, int y, F &&pred) {
        if(l > y || r < x) {
            return -1;
        }
        if(x <= l && r <= y && !pred(info[o])) {
            return -1;
        }
        if(l == r) {
            return l;
        }
        int m = l + r >> 1;
        push(o);
        int res = findLast(o << 1 | 1, m + 1, r, x, y, pred);
        if(res == -1) {
            res = findLast(o << 1, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n - 1, l, r, pred);
    }
};

struct Tag1 {
    int upd = -1;
    void apply(const Tag1 &t) {
        if(t.upd != -1) {
            upd = t.upd;
        }
    }
};

struct Info1 {
    int bel = -1;
    void apply(const Tag1 &t) {
        if(t.upd != -1) {
            bel = t.upd;
        }
    }
};

Info1 operator + (const Info1 &l, const Info1 &r) {
    if(l.bel == -1) return r;
    if(r.bel == -1) return l;
    return {l.bel == r.bel ? l.bel : -1};
}

struct Tag2 {
    int add = 0;
    void apply(const Tag2 &t) {
        add += t.add;
    }
};

struct Info2 {
    int mn = 0, cmn = 0;
    void apply(const Tag2 &t) {
        mn += t.add;
    }
};

Info2 operator + (const Info2 &l, const Info2 &r) {
    if(l.cmn == 0) return r;
    if(r.cmn == 0) return l;
    if(l.mn < r.mn) {
        return {l.mn, l.cmn};
    } else if(r.mn < l.mn) {
        return {r.mn, r.cmn};
    } else {
        return {l.mn, l.cmn + r.cmn};
    }
}

struct info {
    int x, l, r, tag;
    friend bool operator < (const info &a, const info &b) {
        return a.x < b.x;
    }
};

struct FenwickTree {
    inline int lowbit(int o) { return o & -o; }
    int n;
    vector<int> tr;
    FenwickTree() {}
    FenwickTree(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, int d) {
        for(; o < n; o += lowbit(o)) {
            tr[o] += d;
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<info> Line;
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Line.push_back({x1, y1, y2, i});
        Line.push_back({x2, y1, y2, n + i});
        val.push_back(y1);
        val.push_back(y2);
    }
    sort(Line.begin(), Line.end());
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int m = val.size();
    LazySegmentTree<Info1, Tag1> seg(m + 1);
    vector<int> fa(n + 1);
    for(auto [x, l, r, tag] : Line) {
        l = lower_bound(val.begin(), val.end(), l) - val.begin() + 1;
        r = lower_bound(val.begin(), val.end(), r) - val.begin() + 1;
        if(tag <= n) {
            fa[tag] = seg.rangeQuery(l, r).bel;
            if(fa[tag] == -1) {
                fa[tag] = n + 1;
            }
            seg.rangeApply(l, r, {tag});
        } else {
            seg.rangeApply(l, r, {fa[tag - n]});
        }
    }
    int rt = n + 1;
    HLD tr(n + 2);
    for(int i = 1; i <= n; i++) {
        tr.addEdge(fa[i], i);
    }
    tr.work(rt);
    auto &in = tr.in;
    auto &out = tr.out;
    auto &dep = tr.dep;
    auto &top = tr.top;
    auto &parent = tr.parent;
    int mxdep = *max_element(dep.begin(), dep.end());
    vector<int> state(n + 1);
    FenwickTree fen(mxdep + 5);
    LazySegmentTree<Info2, Tag2> seg2(n + 2);
    for(int i = 1; i <= n; i++) {
        seg2.modify(in[i], {0, 1});
    }
    seg2.modify(in[n + 1], {inf, 0});
    while(q--) {
        char op;
        cin >> op;
        if(op == '^') {
            int x;
            cin >> x;
            int d = dep[x];
            int cnt = 0;
            if(state[x] == 0) {
                state[x] ^= 1;
                while(x) {
                    auto [mn, cmn] = seg2.rangeQuery(in[top[x]], in[x]);
                    if(mn == 0) {
                        cnt += cmn;
                    }
                    seg2.rangeApply(in[top[x]], in[x], {1});
                    x = parent[top[x]];
                }
                fen.add(d - cnt + 1, 1);
                fen.add(d + 1, -1);
            } else {
                state[x] ^= 1;
                while(x) {
                    seg2.rangeApply(in[top[x]], in[x], {-1});
                    auto [mn, cmn] = seg2.rangeQuery(in[top[x]], in[x]);
                    if(mn == 0) {
                        cnt += cmn;
                    }
                    x = parent[top[x]];
                }
                fen.add(d - cnt + 1, -1);
                fen.add(d + 1, 1);
            }
        } else {
            int k;
            cin >> k;
            k++;
            cout << fen.query(k) << "\n";
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
