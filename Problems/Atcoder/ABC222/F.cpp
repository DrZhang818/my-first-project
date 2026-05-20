#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

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

struct Tag {
    i64 add = 0;
    void apply(const Tag &t) {
        add += t.add;
    }
};

struct Info {
    i64 mx = -1E18;
    void apply(const Tag &t) {
        mx += t.add;
    }
};

Info operator + (const Info &l, const Info &r) {
    return {max(l.mx, r.mx)};
}

void solve() {
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    vector<i64> D(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> D[i];
    }

    vector<i64> val(n + 1);
    vector<int> in(n + 1), out(n + 1);
    int timer = 1;

    LazySegmentTree<Info, Tag> seg(n + 1);

    auto dfs = [&](auto&& self, int u, int fa) -> void {
        in[u] = timer++;
        seg.modify(in[u], {val[u] + D[u]});
        for(auto [v, c] : adj[u]) {
            if(v == fa) continue;
            val[v] = val[u] + c;
            self(self, v, u);
        }
        out[u] = timer;
    };
    dfs(dfs, 1, 0);

    vector<i64> ans(n + 1);

    auto work = [&](auto&& self, int u, int fa) -> void {
        ans[u] = (seg.rangeQuery(1, in[u] - 1) + seg.rangeQuery(in[u] + 1, n)).mx;

        for(auto [v, c] : adj[u]) {
            if(v == fa) continue;
            int L = in[v], R = out[v] - 1;
            seg.rangeApply(L, R, {-c});
            if(L > 1) seg.rangeApply(1, L - 1, {c});
            if(R < n) seg.rangeApply(R + 1, n, {c});
            self(self, v, u);
            seg.rangeApply(L, R, {c});
            if(L > 1) seg.rangeApply(1, L - 1, {-c});
            if(R < n) seg.rangeApply(R + 1, n, {-c});
        }

    };
    work(work, 1, 0);

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }

}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}