#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

template<class Info>
struct SegmentTree {
    int n;
    vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    SegmentTree(vector<T> init_) {
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

struct Info {
    int mx = -inf;
};

Info operator + (const Info &l, const Info &r) {
    return {max(l.mx, r.mx)};
}
    
inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<int> tr;
    FenwickTree(int n) : n(n), tr(n) {}

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
};

struct Point {
    int x, y, id;
};

struct Query {
    int pos, tag, lo, hi;
    friend bool operator<(const Query& a, const Query& b) {
        if(a.pos != b.pos) return a.pos < b.pos;
        return a.tag < b.tag;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<Point> P(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> P[i].x;
    }    
    for(int i = 1; i <= n; i++) {
        cin >> P[i].y;
        P[i].id = i;
    }

    sort(P.begin() + 1, P.end(),
        [&](const auto& a, const auto& b) {
            return a.x < b.x;
        });

    vector<int> L(n + 1), R(n + 1);
    SegmentTree<Info> seg(n + 1);

    for(int i = n, j = n; i >= 1; i = j) {
        while(j >= 1 && P[j].x == P[i].x) {
            seg.modify(P[j].id, {P[j].y});
            j--;
        }
        for(int k = i; k > j; k--) {
            int idx = P[k].id;
            int l = seg.findLast(1, idx - 1, [&](const Info& info) {
                return info.mx >= P[k].y;
            });
            L[idx] = l == -1 ? 1 : l + 1;
            int r = seg.findFirst(idx + 1, n, [&](const Info& info) {
                return info.mx >= P[k].y;
            });
            R[idx] = r == -1 ? n : r - 1;
        }
    }

    vector<Query> Q;
    for(int i = 1; i <= n; i++) {
        Q.emplace_back(L[i], -2, i, R[i]);
        if(i != n) {
            Q.emplace_back(i + 1, -1, i, R[i]);
        }
    }

    for(int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        Q.emplace_back(l, i, r, r);
    }
    sort(Q.begin(), Q.end());

    FenwickTree fen(n + 5);
    vector<int> ans(q + 1);

    for(auto [pos, tag, lo, hi] : Q) {
        if(tag > 0) {
            ans[tag] = fen.query(lo);
        } else {
            if(tag == -2) {
                fen.add(lo, 1);
                fen.add(hi + 1, -1);
            } else {
                fen.add(lo, -1);
                fen.add(hi + 1, 1);
            }
        }
    }

    for(int i = 1; i <= q; i++) {
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