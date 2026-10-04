#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Beats {
    static constexpr i64 negInf = numeric_limits<i64>::lowest();
    struct Node {
        i64 sum = 0;
        i64 mx = negInf, se = negInf;
        int cnt = 0;
    };
    int n;
    vector<Node> tr;
    Beats(const vector<i64>& a) : n(int(a.size()) - 1), tr(4 * n) {
        build(1, 1, n, a);
    }
    void build(int p, int l, int r, const vector<i64>& a) {
        if(l == r) {
            tr[p] = {a[l], a[l], negInf, 1};
            return;
        }
        int m = (l + r) >> 1;
        build(p << 1, l, m, a);
        build(p << 1 | 1, m + 1, r, a);
        pull(p);
    }
    void pull(int p) {
        auto& a = tr[p << 1];
        auto& b = tr[p << 1 | 1];
        tr[p].sum = a.sum + b.sum;
        if(a.mx == b.mx) {
            tr[p].mx = a.mx;
            tr[p].se = max(a.se, b.se);
            tr[p].cnt = a.cnt + b.cnt;
        } else if(a.mx > b.mx) {
            tr[p].mx = a.mx;
            tr[p].se = max(a.se, b.mx);
            tr[p].cnt = a.cnt;
        } else {
            tr[p].mx = b.mx;
            tr[p].se = max(a.mx, b.se);
            tr[p].cnt = b.cnt;
        }
    }
    void applyChmin(int p, i64 x) {
        if(x >= tr[p].mx) {
            return;
        }
        tr[p].sum -= (__int128(tr[p].mx) - x) * tr[p].cnt;
        tr[p].mx = x;
    }
    void push(int p) {
        applyChmin(p << 1, tr[p].mx);
        applyChmin(p << 1 | 1, tr[p].mx);
    }
    void chmin(int p, int l, int r, int x, int y, i64 v) {
        if(r < x || y < l || v >= tr[p].mx) {
            return;
        }
        if(l == r || (x <= l && r <= y && v > tr[p].se)) {
            applyChmin(p, v);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        chmin(p << 1, l, m, x, y, v);
        chmin(p << 1 | 1, m + 1, r, x, y, v);
        pull(p);
    }
    void chmin(int l, int r, i64 v) {
        chmin(1, 1, n, l, r, v);
    }
    i64 sum(int p, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return tr[p].sum;
        }
        push(p);
        int m = (l + r) >> 1;
        i64 res = 0;
        if(x <= m) {
            res += sum(p << 1, l, m, x, y);
        }
        if(y > m) {
            res += sum(p << 1 | 1, m + 1, r, x, y);
        }
        return res;
    }
    i64 sum(int l, int r) {
        return sum(1, 1, n, l, r);
    }
    i64 maxi(int p, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return tr[p].mx;
        }
        push(p);
        int m = (l + r) >> 1;
        i64 res = negInf;
        if(x <= m) {
            res = max(res, maxi(p << 1, l, m, x, y));
        }
        if(y > m) {
            res = max(res, maxi(p << 1 | 1, m + 1, r, x, y));
        }
        return res;
    }
    i64 maxi(int l, int r) {
        return maxi(1, 1, n, l, r);
    }
};
