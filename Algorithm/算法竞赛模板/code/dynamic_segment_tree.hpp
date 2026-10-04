#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class Info> struct DynSeg {
    struct Node {
        int ls = 0, rs = 0;
        Info val;
    };
    i64 L, R;
    vector<Node> tr;
    DynSeg(i64 l, i64 r) : L(l), R(r), tr(1) {
    }
    int newNode() {
        tr.push_back({});
        return int(tr.size()) - 1;
    }
    void pull(int p) {
        tr[p].val = tr[tr[p].ls].val + tr[tr[p].rs].val;
    }
    int modify(int p, i64 l, i64 r, i64 x, const Info& v) {
        if(!p) {
            p = newNode();
        }
        if(l == r) {
            tr[p].val = v;
            return p;
        }
        i64 m = l + (r - l) / 2;
        if(x <= m) {
            tr[p].ls = modify(tr[p].ls, l, m, x, v);
        } else {
            tr[p].rs = modify(tr[p].rs, m + 1, r, x, v);
        }
        pull(p);
        return p;
    }
    void modify(int& root, i64 x, const Info& v) {
        root = modify(root, L, R, x, v);
    }
    Info query(int p, i64 l, i64 r, i64 x, i64 y) const {
        if(!p) {
            return Info();
        }
        if(x <= l && r <= y) {
            return tr[p].val;
        }
        i64 m = l + (r - l) / 2;
        if(y <= m) {
            return query(tr[p].ls, l, m, x, y);
        }
        if(x > m) {
            return query(tr[p].rs, m + 1, r, x, y);
        }
        return query(tr[p].ls, l, m, x, y) + query(tr[p].rs, m + 1, r, x, y);
    }
    Info query(int root, i64 l, i64 r) const {
        return query(root, L, R, l, r);
    }
};
