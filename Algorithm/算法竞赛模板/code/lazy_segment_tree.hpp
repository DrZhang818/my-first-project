#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class Info, class Tag> struct LazySeg {
    int n = 0;
    vector<Info> tr;
    vector<Tag> lz;
    LazySeg(int n_ = 0, const Info& v = Info()) {
        init(n_, v);
    }
    template <class T> LazySeg(const vector<T>& a) {
        init(a);
    }
    void init(int n_, const Info& v = Info()) {
        init(vector<Info>(n_ + 1, v));
    }
    template <class T> void init(const vector<T>& a) {
        n = int(a.size()) - 1;
        tr.assign(4 * max(1, n), Info());
        lz.assign(4 * max(1, n), Tag());
        if(n) {
            build(1, 1, n, a);
        }
    }
    template <class T> void build(int p, int l, int r, const vector<T>& a) {
        if(l == r) {
            tr[p] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        pull(p);
    }
    void pull(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void apply(int p, const Tag& v) {
        tr[p].apply(v);
        lz[p].apply(v);
    }
    void push(int p) {
        apply(p << 1, lz[p]);
        apply(p << 1 | 1, lz[p]);
        lz[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info& v) {
        if(l == r) {
            tr[p] = v;
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        if(x <= m) {
            modify(p << 1, l, m, x, v);
        } else {
            modify(p << 1 | 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int x, const Info& v) {
        modify(1, 1, n, x, v);
    }
    Info query(int p, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return tr[p];
        }
        push(p);
        int m = (l + r) >> 1;
        if(y <= m) {
            return query(p << 1, l, m, x, y);
        }
        if(x > m) {
            return query(p << 1 | 1, m + 1, r, x, y);
        }
        return query(p << 1, l, m, x, y) + query(p << 1 | 1, m + 1, r, x, y);
    }
    Info query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    void apply(int p, int l, int r, int x, int y, const Tag& v) {
        if(x <= l && r <= y) {
            apply(p, v);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        if(x <= m) {
            apply(p << 1, l, m, x, y, v);
        }
        if(y > m) {
            apply(p << 1 | 1, m + 1, r, x, y, v);
        }
        pull(p);
    }
    void apply(int l, int r, const Tag& v) {
        apply(1, 1, n, l, r, v);
    }
    template <class F> int first(int p, int l, int r, int x, int y, Info& cur, F& pred) {
        if(r < x || y < l) {
            return -1;
        }
        if(x <= l && r <= y) {
            Info nxt = cur + tr[p];
            if(!pred(nxt)) {
                cur = nxt;
                return -1;
            }
            if(l == r) {
                return l;
            }
        }
        push(p);
        int m = (l + r) >> 1;
        int res = first(p << 1, l, m, x, y, cur, pred);
        if(res == -1) {
            res = first(p << 1 | 1, m + 1, r, x, y, cur, pred);
        }
        return res;
    }
    template <class F> int first(int l, int r, F pred) {
        Info cur;
        return first(1, 1, n, l, r, cur, pred);
    }
    template <class F> int last(int p, int l, int r, int x, int y, Info& cur, F& pred) {
        if(r < x || y < l) {
            return -1;
        }
        if(x <= l && r <= y) {
            Info nxt = tr[p] + cur;
            if(!pred(nxt)) {
                cur = nxt;
                return -1;
            }
            if(l == r) {
                return l;
            }
        }
        push(p);
        int m = (l + r) >> 1;
        int res = last(p << 1 | 1, m + 1, r, x, y, cur, pred);
        if(res == -1) {
            res = last(p << 1, l, m, x, y, cur, pred);
        }
        return res;
    }
    template <class F> int last(int l, int r, F pred) {
        Info cur;
        return last(1, 1, n, l, r, cur, pred);
    }
};
