#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    int sz = 1;
    vector<Info> info;
    vector<Tag> tag;
    vector<int> L, R;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    // template<class T>
    // LazySegmentTree(vector<T> init_) {
    //     init(init_);
    // }
    void init(int n_, Info v_ = Info()) {
        n = n_;
        info.assign(2, Info(0, n));
        tag.assign(2, Tag());
        L.assign(2, {});
        R.assign(2, {});
    }
    // template<class T>
    // void init(vector<T> init_) {
    //     n = init_.size();
    // }
    int add(int len) {
        info.push_back(Info(0, len));
        tag.push_back(Tag());
        L.push_back({});
        R.push_back({});
        return ++sz;
    }
    void pull(int o) {
        if(!L[o]) {
            info[o] = Info(0, info[o].len + 1 >> 1) + info[R[o]];
        } else if(!R[o]) {
            info[o] = info[L[o]] + Info(0, info[o].len >> 1);
        } else {
            info[o] = info[L[o]] + info[R[o]];
        }
    }
    void apply(int o, const Tag &v) {
        info[o].apply(v);
        tag[o].apply(v);
    }
    void push(int o) {
        if(tag[o] == Tag()) {
            return;
        }
        if(!L[o]) {
            L[o] = add(info[o].len + 1 >> 1);
        }
        if(!R[o]) {
            R[o] = add(info[o].len >> 1);
        }
        apply(L[o], tag[o]);
        apply(R[o], tag[o]);
        tag[o] = Tag();
    }
    void modify(int o, int l, int r, int x, const Info &v) {
        if(l == r) {
            info[o] = v;
            return ;
        }
        int m = l + r >> 1;
        push(o);
        if(x <= m) {
            if(!L[o]) L[o] = add(info[o].len + 1 >> 1);
            modify(L[o], l, m, x, v);
        } else {
            if(!R[o]) R[o] = add(info[o].len >> 1);
            modify(R[o], m + 1, r, x, v);
        }
        pull(o);
    }
    void modify(int x, const Info &v) {
        modify(1, 0, n - 1, x, v);
    }
    Info rangeQuery(int o, int l, int r, int x, int y) {
        if(!o || l > y || r < x) {
            return Info();
        }
        if(x <= l && r <= y) {
            return info[o];
        }
        int m = l + r >> 1;
        push(o);
        return rangeQuery(L[o], l, m, x, y) + rangeQuery(R[o], m + 1, r, x, y);
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
        if(l <= y && m >= x) {
            if(!L[o]) L[o] = add(info[o].len + 1 >> 1);
            rangeApply(L[o], l, m, x, y, v);
        }
        if(m + 1 <= y && r >= x) {
            if(!R[o]) R[o] = add(info[o].len >> 1);
            rangeApply(R[o], m + 1, r, x, y, v);
        }
        pull(o);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n - 1, l, r, v);
    }
};

struct Tag {
    int add = 0;
    void apply(const Tag &t) {
        add += t.add;
    }
    bool operator == (const Tag &p) const {
        return add == p.add;
    }
};

struct Info {
    ll sum = 0;
    int len = 0;
    void apply(const Tag &t) {
        sum += 1LL * len * t.add;
    }
};

Info operator + (const Info &l, const Info &r) {
    return {l.sum + r.sum, l.len + r.len};
}

void solve() {
    int n, m;
    cin >> n >> m;
    LazySegmentTree<Info, Tag> seg(n + 1);
    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            seg.rangeApply(l, r, {k});
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.rangeQuery(l, r).sum << "\n";
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
