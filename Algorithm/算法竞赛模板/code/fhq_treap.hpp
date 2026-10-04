#pragma once
#include <bits/stdc++.h>
using namespace std;
struct FHQ {
    struct Node {
        int ls = 0, rs = 0;
        int val = 0, sz = 0;
        uint32_t pri = 0;
    };
    vector<Node> tr;
    int root = 0;
    mt19937 rng;
    FHQ(int q = 0,
        uint32_t seed = uint32_t(chrono::steady_clock::now().time_since_epoch().count()))
        : tr(1), rng(seed) {
        tr.reserve(q + 1);
    }
    int size(int p) const {
        return tr[p].sz;
    }
    int size() const {
        return size(root);
    }
    int newNode(int v) {
        tr.push_back({0, 0, v, 1, rng()});
        return int(tr.size()) - 1;
    }
    void pull(int p) {
        tr[p].sz = size(tr[p].ls) + size(tr[p].rs) + 1;
    }
    void splitLess(int p, int v, int& x, int& y) {
        if(!p) {
            x = y = 0;
            return;
        }
        if(tr[p].val < v) {
            x = p;
            splitLess(tr[p].rs, v, tr[p].rs, y);
        } else {
            y = p;
            splitLess(tr[p].ls, v, x, tr[p].ls);
        }
        pull(p);
    }
    void splitLE(int p, int v, int& x, int& y) {
        if(!p) {
            x = y = 0;
            return;
        }
        if(tr[p].val <= v) {
            x = p;
            splitLE(tr[p].rs, v, tr[p].rs, y);
        } else {
            y = p;
            splitLE(tr[p].ls, v, x, tr[p].ls);
        }
        pull(p);
    }
    int merge(int x, int y) {
        if(!x || !y) {
            return x | y;
        }
        if(tr[x].pri > tr[y].pri) {
            tr[x].rs = merge(tr[x].rs, y);
            pull(x);
            return x;
        }
        tr[y].ls = merge(x, tr[y].ls);
        pull(y);
        return y;
    }
    void insert(int v) {
        int x, y;
        splitLE(root, v, x, y);
        root = merge(merge(x, newNode(v)), y);
    }
    bool erase(int v) {
        int x, y, z;
        splitLess(root, v, x, y);
        splitLE(y, v, y, z);
        bool ok = y != 0;
        if(y) {
            y = merge(tr[y].ls, tr[y].rs);
        }
        root = merge(x, merge(y, z));
        return ok;
    }
    int rank(int v) {
        int x, y;
        splitLess(root, v, x, y);
        int res = size(x) + 1;
        root = merge(x, y);
        return res;
    }
    int kth(int k) const {
        int p = root;
        while(p) {
            int s = size(tr[p].ls);
            if(k == s + 1) {
                return tr[p].val;
            }
            if(k <= s) {
                p = tr[p].ls;
            } else {
                k -= s + 1;
                p = tr[p].rs;
            }
        }
        assert(false);
        return 0;
    }
    bool prev(int v, int& res) {
        int x, y;
        splitLess(root, v, x, y);
        int p = x;
        while(p && tr[p].rs) {
            p = tr[p].rs;
        }
        if(p) {
            res = tr[p].val;
        }
        root = merge(x, y);
        return p != 0;
    }
    bool next(int v, int& res) {
        int x, y;
        splitLE(root, v, x, y);
        int p = y;
        while(p && tr[p].ls) {
            p = tr[p].ls;
        }
        if(p) {
            res = tr[p].val;
        }
        root = merge(x, y);
        return p != 0;
    }
};
