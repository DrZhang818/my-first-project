#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = ll(1E18);


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
    ll rangeApply(int o, int l, int r, int x, int y, const Tag &v) {
        if(l > y || r < x || info[o].cnt == 0) {
            return 0;
        }
        if(l == r) {
            if(info[o].min > v.add) {
                info[o].min -= v.add;
                return v.add;
            } else {
                ll t = info[o].min;
                info[o].min = inf;
                info[o].cnt = 0;
                return t;
            }
        }
        if(x <= l && r <= y) {
            if(info[o].min > v.add) {
                apply(o, v);
                return info[o].cnt * v.add;
            }
        }
        int m = l + r >> 1;
        push(o);
        ll res = 0;
        res += rangeApply(o << 1, l, m, x, y, v);
        res += rangeApply(o << 1 | 1, m + 1, r, x, y, v);
        pull(o);
        return res;
    }
    ll rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n - 1, l, r, v);
    }
};

struct Tag {
    ll add = 0;
    void apply(const Tag &t) {
        add += t.add;
    }
};

struct Info {
    int cnt = 1;
    ll min = 0;
    void apply(const Tag &t) {
        min -= t.add;
    }
};

Info operator + (const Info &l, const Info &r) {
    return {l.cnt + r.cnt, min(l.min, r.min)};
}



void solve() {
    int n;
    cin >> n;
    LazySegmentTree<Info, Tag> seg(n);
    for(int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        seg.modify(i, {1, x});
    }
    int q;
    cin >> q;
    while(q--) { 
        int l, r, k;
        cin >> l >> r >> k;
        l--;
        r--;
        cout << seg.rangeApply(l, r, {k}) << "\n";
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
