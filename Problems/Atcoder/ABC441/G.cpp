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
        if(tag[o] == Tag()) return;
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
        if(v.add > 0 && info[o].dir == 1) {
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
};

struct Tag {
    ll add = 0;
    int s = 0;
    int zero = 0;
    void apply(const Tag &t) {
        if(t.zero) {
            add = 0;
            zero = 1;
        }
        if(t.s) {
            s ^= t.s;
        }
        if(t.add > 0) {
            add += t.add;
        }
    }
};

bool operator==(const Tag& a, const Tag& b) {
    return a.add == b.add && a.s == b.s && a.zero == b.zero;
}

struct Info {
    ll mx = 0;
    int dir = 0;
    void apply(const Tag &t) {
        if(t.zero) {
            mx = 0;
        }
        if(dir != 2) {
            dir ^= t.s;
        }
        if(dir != 1) {
            mx += t.add;
        }
    }
};

Info operator + (const Info& l, const Info& r) {
    int ndir;
    if(l.dir == r.dir) {
        ndir = l.dir;
    } else {
        ndir = 2;
    }
    return {max(l.mx, r.mx), ndir};
}

void solve() {  
    int n, q;
    cin >> n >> q;
    LazySegmentTree<Info, Tag> seg(n + 1);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            seg.rangeApply(l, r, {x, 0, 0});
        } else if(op == 2) {
            int l, r;
            cin >> l >> r;
            seg.rangeApply(l, r, {0, 1, 1});
        } else {
            int l, r;
            cin >> l >> r;
            ll res = seg.rangeQuery(l, r).mx;
            cout << res << "\n";
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
