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
    int upd = -inf;
    void apply(const Tag &t) {
        if(t.upd != -inf) {
            upd = max(upd, t.upd);            
        }
    }
};

struct Info {
    int mx = -inf;
    void apply(const Tag &t) {
        if(t.upd != -inf) {
            mx = max(mx, t.upd);
        }
    }
};

Info operator + (const Info &l, const Info &r) {
    return {max(l.mx, r.mx)};
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(3, vector<int>(n + 1));
    for(int i = 1; i <= 2; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    vector<array<int,2>> mn(n + 2, {inf,inf}), mx(n + 2, {-inf,-inf});
    for(int i = 1; i <= n; i++) {
        mn[i][0] = min(a[1][i], mn[i - 1][0]);
        mx[i][0] = max(a[1][i], mx[i - 1][0]);
    }
    for(int i = n; i >= 1; i--) {
        mn[i][1] = min(a[2][i], mn[i + 1][1]);
        mx[i][1] = max(a[2][i], mx[i + 1][1]);
    }
    ll ans = 0;
    LazySegmentTree<Info, Tag> tr(2 * n + 5);
    for(int j = 1; j <= n; j++) {
        int L = min(mn[j][0], mn[j][1]);
        int R = max(mx[j][0], mx[j][1]);
        tr.rangeApply(R, 2 * n, {L});
    }
    for(int i = 1; i <= 2 * n; i++) {
        int val = tr.rangeQuery(i, i).mx;
        if(val == -inf) continue;
        ans += val;
    }
    cout << ans << "\n";
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
