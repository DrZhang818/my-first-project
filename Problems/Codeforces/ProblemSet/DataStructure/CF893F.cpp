#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

template<class Info>
struct PersistentSegmentTree {
    struct Node {
        int l = 0, r = 0;
        Info info;
    };
    int n;
    vector<Node> nodes;

    PersistentSegmentTree() : n(0) {}
    PersistentSegmentTree(int n_, int q = 0) {
        init(n_, q);
    }

    void init(int n_, int q = 0) {
        n = n_;
        nodes.clear();
        nodes.reserve(4 * n + (q > 0 ? q * (__lg(n) + 2) : 0));
        nodes.push_back({0, 0, Info()});
    }

    //下标从1开始
    template<class T>
    int build(const vector<T>& init_) {
        auto dfs = [&](auto &&self, int l, int r) -> int {
            int u = newNode();
            if(l == r) {
                if(l < (int)init_.size()) nodes[u].info = init_[l];
                return u;
            }
            int mid = l + r >> 1;
            nodes[u].l = self(self, l, mid);
            nodes[u].r = self(self, mid + 1, r);
            pull(u);
            return u;
        };
        return dfs(dfs, 1, n);
    }
    int build() {
        auto dfs = [&](auto &&self, int l, int r) -> int {
            int u = newNode();
            if(l == r) return u;
            int mid = l + r >> 1;
            nodes[u].l = self(self, l, mid);
            nodes[u].r = self(self, mid + 1, r);
            pull(u);
            return u;
        };
        return dfs(dfs, 1, n);
    }
    int newNode() {
        nodes.push_back({0, 0, Info()});
        return nodes.size() - 1;
    }
    int copyNode(int src) {
        Node tmp = nodes[src];
        nodes.push_back(tmp);
        return nodes.size() - 1;
    }
    void pull(int u) {
        if(u) nodes[u].info = nodes[nodes[u].l].info + nodes[nodes[u].r].info;
    }
    int modify(int prev, int l, int r, int x, const Info& v) {
        int u = copyNode(prev);
        if(l == r) {
            nodes[u].info = v;

            //需要累加时这样写
            //nodes[u].info = nodes[u].info + v;
            return u;
        }
        int mid = l + r >> 1;
        if(x <= mid) {
            nodes[u].l = modify(nodes[prev].l, l, mid, x, v);
        } else {
            nodes[u].r = modify(nodes[prev].r, mid + 1, r, x, v);
        }
        pull(u);
        return u;
    }
    int modify(int prev, int x, const Info& v) {
        return modify(prev, 1, n, x, v);
    }
    Info query(int u, int l, int r, int x, int y) {
        if(!u) return Info();
        if(x <= l && r <= y) {
            return nodes[u].info;
        }
        int mid = l + r >> 1;
        if(y <= mid) {
            return query(nodes[u].l, l, mid, x, y);
        }
        if(x > mid) {
            return query(nodes[u].r, mid + 1, r, x, y);
        }
        return query(nodes[u].l, l, mid, x, y) + query(nodes[u].r, mid + 1, r, x, y);
    }
    Info query(int u, int x, int y) {
        return query(u, 1, n, x, y);
    }
};

struct Info {
    int mn = inf;
};

Info operator+(const Info& a, const Info& b) {
    return {min(a.mn, b.mn)};
}

void solve() {  
    int n, rt;
    cin >> n >> rt;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector adj(n + 1, vector<int>{});
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int idx = 0;
    vector<int> dfn(n + 1), dep(n + 1), R(n + 1);
    [&](this auto &&self, int u, int fa) -> void {
        dfn[u] = ++idx;
        dep[u] = dep[fa] + 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
        R[u] = idx;
    } (rt, 0);

    PersistentSegmentTree<Info> seg(n, n);
    vector<int> roots(n + 1);
    roots[0] = seg.build();

    queue<int> que;
    que.push(rt);
    int d = 0;
    while(!que.empty()) {
        d++;
        roots[d] = roots[d - 1];
        int sz = que.size();
        while(sz--) {
            int u = que.front(); que.pop();
            roots[d] = seg.modify(roots[d], dfn[u], {a[u]});
            for(int v : adj[u]) {
                if(dep[v] > dep[u]) {
                    que.push(v);
                }
            }
        }
    }
    int q;
    cin >> q;
    int ans = 0;
    while(q--) {
        int u, k;
        cin >> u >> k;
        u = (u + ans) % n + 1;
        k = (k + ans) % n;
        int x = min(dep[u] + k, d);
        ans = seg.query(roots[x], dfn[u], R[u]).mn;
        cout << ans << "\n";        
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
