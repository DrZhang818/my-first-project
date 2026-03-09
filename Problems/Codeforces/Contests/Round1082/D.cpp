#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

template<class Info>
struct LazySegmentTree {
    int n;
    vector<Info> info;
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
    void modify(int o, int l, int r, int x, const Info &v) {
        if(l == r) {
            info[o] = v;
            return ;
        }
        int m = l + r >> 1;
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
        return rangeQuery(o << 1, l, m, x, y) + rangeQuery(o << 1 | 1, m + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
};

struct Info {
    int mx = 0;
    int len = 1;
    int pre = 0;
    int suf = 0;
    i64 ans = 0;
};

Info operator + (const Info &l, const Info &r) {
    if(l.len == 0) return r;
    if(r.len == 0) return l;
    Info res;
    res.mx = max(l.mx, r.mx);
    res.len = l.len + r.len;
    if(l.mx > r.mx) {
        res.pre = l.pre;
        res.ans = l.ans;
    } else if(r.mx > l.mx) {
        res.suf = r.suf;
        res.ans = r.ans;
    } else {
        res.pre = l.pre + (l.pre == l.len ? r.pre : 0);
        res.suf = r.suf + (r.suf == r.len ? l.suf : 0);
        res.ans = l.ans + r.ans + 1LL * l.suf * r.pre;
    }
    return res;
}

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<set<int>> st(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        st[x].insert(i);
    }

    LazySegmentTree<Info> seg(n + 1);
    seg.modify(0, {0, 1, 0, 0, 0});

    for(int i = 1; i <= n; i++) {
        if(!st[i].empty()) {
            int L = *st[i].begin();
            int R = *st[i].rbegin();
            seg.modify(L, {R - L, 1, 1, 1, 1});
        }
    }

    auto remove = [&](int i, int x) {
        int L = *st[x].begin();
        if(L == i) {
            seg.modify(L, {0, 1, 0, 0, 0});
        }
        st[x].erase(i);
        if(!st[x].empty()) {
            int L = *st[x].begin();
            int R = *st[x].rbegin();
            seg.modify(L, {R - L, 1, 1, 1, 1});
        }
    };

    auto add = [&](int i, int x) {
        if(!st[x].empty()) {
            int L = *st[x].begin();
            if(i < L) {
                seg.modify(L, {0, 1, 0, 0, 0});
            }
        }
        st[x].insert(i);
        int L = *st[x].begin();
        int R = *st[x].rbegin();
        seg.modify(L, {R - L, 1, 1, 1, 1});
    };

    while(q--) {
        int i, x;
        cin >> i >> x;

        if(a[i] != x) {
            remove(i, a[i]);
            add(i, x);
            a[i] = x;
        }

        auto res = seg.rangeQuery(1, n);
        if(res.mx == 0) {
            cout << 0 << " " << 0 << "\n";
            continue;
        }
        cout << res.mx << " " << res.ans << "\n";
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
