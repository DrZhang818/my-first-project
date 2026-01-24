#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

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
    int findFirst(int o, int l, int r, int x, int y, int L, int &val) {
        if(l > y || r < x) {
            return -1;
        }
        int mn = min(val, info[o].mn);
        if(x <= l && r <= y) {
            if(mn > r - L) {
                val = mn;
                return -1;
            }
        }
        if(l == r) {
            return l;
        }
        push(o);
        int m = l + r >> 1;
        int res = findFirst(o << 1, l, m, x, y, L, val);
        if(res != -1) return res;
        return findFirst(o << 1 | 1, m + 1, r, x, y, L, val);
    } 
    int findFirst(int l, int r) {
        int val = inf;
        return findFirst(1, 0, n - 1, l, r, l, val);
    }
};

struct Tag {
    int upd = 0;
    void apply(const Tag &t) {
        if(t.upd) {
            upd = t.upd;
        }
    }
};

struct Info {
    int mn = inf;
    void apply(const Tag &t) {
        if(t.upd) {
            mn = min(mn, t.upd);
        }
    }
};

Info operator + (const Info &l, const Info &r) {
    return {min(l.mn, r.mn)};
}


void solve() {
    int n, q;
    cin >> n >> q;

    LazySegmentTree<Info,Tag> seg(n + 1);
    
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        seg.modify(i, {x});
    }

    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i, x;
            cin >> i >> x;
            seg.modify(i, {x});
        } else {
            int l, r;
            cin >> l >> r;
            int pos = seg.findFirst(l, r);
            if(pos == -1 || seg.rangeQuery(l, pos).mn != pos - l) {
                cout << 0 << "\n";
            } else {
                cout << 1 << "\n";
            }
        } 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
 