#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class Info> struct PST {
    struct Node {
        int ls = 0, rs = 0;
        Info val;
    };
    int n;
    vector<Node> tr;
    PST(int n_ = 0, int q = 0) : n(n_), tr(1) {
        if(n && q) {
            tr.reserve(size_t(q) * ((n ? 32 - __builtin_clz((unsigned)n) : 0) + 1) + 1);
        }
    }
    int clone(int p) {
        tr.push_back(tr[p]);
        return int(tr.size()) - 1;
    }
    void pull(int p) {
        tr[p].val = tr[tr[p].ls].val + tr[tr[p].rs].val;
    }
    int modify(int p, int l, int r, int x, const Info& v) {
        int u = clone(p);
        if(l == r) {
            tr[u].val.apply(v);
            return u;
        }
        int m = (l + r) >> 1;
        if(x <= m) {
            tr[u].ls = modify(tr[p].ls, l, m, x, v);
        } else {
            tr[u].rs = modify(tr[p].rs, m + 1, r, x, v);
        }
        pull(u);
        return u;
    }
    int modify(int root, int x, const Info& v) {
        return modify(root, 1, n, x, v);
    }
    Info query(int p, int l, int r, int x, int y) const {
        if(!p) {
            return Info();
        }
        if(x <= l && r <= y) {
            return tr[p].val;
        }
        int m = (l + r) >> 1;
        if(y <= m) {
            return query(tr[p].ls, l, m, x, y);
        }
        if(x > m) {
            return query(tr[p].rs, m + 1, r, x, y);
        }
        return query(tr[p].ls, l, m, x, y) + query(tr[p].rs, m + 1, r, x, y);
    }
    Info query(int root, int l, int r) const {
        return query(root, 1, n, l, r);
    }
    Info query(int a, int b, int l, int r, int x, int y) const {
        if(x <= l && r <= y) {
            return tr[b].val - tr[a].val;
        }
        int m = (l + r) >> 1;
        if(y <= m) {
            return query(tr[a].ls, tr[b].ls, l, m, x, y);
        }
        if(x > m) {
            return query(tr[a].rs, tr[b].rs, m + 1, r, x, y);
        }
        return query(tr[a].ls, tr[b].ls, l, m, x, y) +
               query(tr[a].rs, tr[b].rs, m + 1, r, x, y);
    }
    Info query(int a, int b, int l, int r) const {
        return query(a, b, 1, n, l, r);
    }
    template <class F>
    int first(int a, int b, int l, int r, int x, int y, Info& cur, F& pred) const {
        if(r < x || y < l) {
            return -1;
        }
        if(x <= l && r <= y) {
            Info nxt = cur + (tr[b].val - tr[a].val);
            if(!pred(nxt)) {
                cur = nxt;
                return -1;
            }
            if(l == r) {
                return l;
            }
        }
        int m = (l + r) >> 1;
        int p = first(tr[a].ls, tr[b].ls, l, m, x, y, cur, pred);
        if(p == -1) {
            p = first(tr[a].rs, tr[b].rs, m + 1, r, x, y, cur, pred);
        }
        return p;
    }
    template <class F> int first(int a, int b, int l, int r, F pred) const {
        Info cur;
        return first(a, b, 1, n, l, r, cur, pred);
    }
    template <class F>
    int last(int a, int b, int l, int r, int x, int y, Info& cur, F& pred) const {
        if(r < x || y < l) {
            return -1;
        }
        if(x <= l && r <= y) {
            Info nxt = (tr[b].val - tr[a].val) + cur;
            if(!pred(nxt)) {
                cur = nxt;
                return -1;
            }
            if(l == r) {
                return l;
            }
        }
        int m = (l + r) >> 1;
        int p = last(tr[a].rs, tr[b].rs, m + 1, r, x, y, cur, pred);
        if(p == -1) {
            p = last(tr[a].ls, tr[b].ls, l, m, x, y, cur, pred);
        }
        return p;
    }
    template <class F> int last(int a, int b, int l, int r, F pred) const {
        Info cur;
        return last(a, b, 1, n, l, r, cur, pred);
    }
};
