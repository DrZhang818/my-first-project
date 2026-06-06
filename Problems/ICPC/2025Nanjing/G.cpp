#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
using i64 = long long;

constexpr i64 inf = 1E18;

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
    i64 mn = inf;
    void apply(const Tag &t) {
        // mn = min(mn, t.mn);
    }
};

struct Info {
    i64 mn = inf;
    int id = -1;
    void apply(const Tag &t) {
        // mn = min(mn, t.mn);
    }
};

Info operator + (const Info &l, const Info &r) {
    if(l.mn <= r.mn) {
        return l;
    } else {
        return r;
    }
}

struct Index {
    int val, id;

    Index(int x = 0, int y = 0) {
        val = x;
        id = y;
    }

    friend bool operator < (Index A, Index B) {
        if(A.val != B.val) return A.val < B.val;
        return A.id < B.id;
    }
} I[200001];

struct Bucket {
    int v, l, id;

    Bucket(int x = 0, int y = 0, int z = 0) {
        v = x;
        l = y;
        id = z;
    }

    friend bool operator < (Bucket A, Bucket B) {
        if(A.l != B.l) return A.l < B.l;
        if(A.v != B.v) return A.v < B.v;
        return A.id < B.id;
    }

    friend bool operator > (Bucket A, Bucket B) {
        if(A.v != B.v) return A.v > B.v;
        return A.id < B.id;
    }
} B[200001];

int t, n, q;
int v[200001];
int l[200001];
bool vis[200001];
long long ans[200001];
vector<pair<int, int> > vec;
set<Bucket> st;

struct PAIR {
    i64 l, v;
    int id;
    friend bool operator<(const PAIR& a, const PAIR& b) {
        if(a.l != b.l) return a.l < b.l;
        return a.id < b.id;
    }
};

int main() {
    scanf("%d", &t);
    while(t--) {
        st.clear();
        vec.clear();
        scanf("%d", &n);
        for(int i = 1;i <= n;i++) {
            scanf("%d", &v[i]);
            vis[i] = false;
        }
        for(int i = 1;i <= n;i++) {
            scanf("%d", &l[i]);
            B[i] = Bucket(v[i], l[i], i);
            st.insert(B[i]);
        }

        LazySegmentTree<Info, Tag> seg(n + 1);
        vector<PAIR> U(n);
        for(int i = 0; i < n; i++) {
            U[i] = {B[i + 1].l, B[i + 1].v, B[i + 1].id};
        }

        auto V = U;
        sort(V.begin(), V.end());
        V.erase(unique(V.begin(), V.end()), V.end());
        vector<int> rev(n + 1), to(n + 1);
        for(int i = 0; i < n; i++) {
            auto idx = lower_bound(V.begin(), V.end(), U[i]) - V.begin();
            rev[idx] = U[i].id;
            to[U[i].id] = idx;
            seg.modify(idx, {U[i].v, U[i].id});
        }

        sort(B + 1, B + n + 1, greater<Bucket>());
        for(int i = 1;i <= n;i++) {
            if(vis[B[i].id]) continue;

            auto cur = PAIR{B[i].l, -1, -1};
            auto idx = lower_bound(V.begin(), V.end(), cur) - V.begin() - 1;

            if(idx >= 0) {
                auto res = seg.rangeQuery(0, idx).id;
            }

            // st.erase(B[i]);
            // set<Bucket>::iterator it = st.lower_bound(Bucket(0, B[i].l - 1));
            vis[B[i].id] = true;

            seg.modify()

            if(it != st.end()) {
                Bucket b = *it;
                st.erase(it);
                vec.push_back(make_pair(B[i].id, b.id));
                vis[b.id] = true;
            } else vec.push_back(make_pair(B[i].id, 0));
        }
        for(pair<int, int> p : vec) {
            printf("%d %d|", p.first, p.second);
        }
        scanf("%d", &q);
        for(int i = 1, t;i <= q;i++) {
            scanf("%d", &t);
            I[i] = Index(t, i);
        }
        sort(I + 1, I + q + 1);

    }
    return 0;
}
