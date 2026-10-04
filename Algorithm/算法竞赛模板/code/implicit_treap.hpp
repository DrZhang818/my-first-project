#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class Policy> struct Treap {
    using Val = typename Policy::Val;
    using Info = typename Policy::Info;
    using Tag = typename Policy::Tag;
    struct Node {
        int ls = 0, rs = 0, sz = 1;
        uint32_t pri = 0;
        Val val{};
        Info info{};
        Tag tag{};
        bool rev = false;
    };
    vector<Node> tr;
    mt19937 rng;
    Treap(int q = 0,
          uint32_t seed = uint32_t(chrono::steady_clock::now().time_since_epoch().count()))
        : tr(1), rng(seed) {
        tr.reserve(q + 1);
        tr[0].sz = 0;
        tr[0].info = Policy::identity();
        tr[0].tag = Policy::tagIdentity();
    }
    int size(int p) const {
        return tr[p].sz;
    }
    Info info(int p) const {
        return p ? tr[p].info : Policy::identity();
    }
    int newNode(const Val& v) {
        tr.push_back({});
        int p = int(tr.size()) - 1;
        tr[p].pri = rng();
        tr[p].val = v;
        tr[p].info = Policy::make(v);
        tr[p].tag = Policy::tagIdentity();
        return p;
    }
    void pull(int p) {
        tr[p].sz = size(tr[p].ls) + size(tr[p].rs) + 1;
        tr[p].info = Policy::merge(Policy::merge(info(tr[p].ls), Policy::make(tr[p].val)),
                                   info(tr[p].rs));
    }
    void applyTag(int p, const Tag& tag) {
        if(!p || Policy::tagEmpty(tag)) {
            return;
        }
        Policy::apply(tr[p].val, tr[p].info, tr[p].sz, tag);
        Policy::compose(tr[p].tag, tag);
    }
    void applyRev(int p) {
        if(!p) {
            return;
        }
        swap(tr[p].ls, tr[p].rs);
        tr[p].rev ^= 1;
        Policy::reverseInfo(tr[p].info);
    }
    void push(int p) {
        if(tr[p].rev) {
            applyRev(tr[p].ls);
            applyRev(tr[p].rs);
            tr[p].rev = false;
        }
        if(!Policy::tagEmpty(tr[p].tag)) {
            applyTag(tr[p].ls, tr[p].tag);
            applyTag(tr[p].rs, tr[p].tag);
            tr[p].tag = Policy::tagIdentity();
        }
    }
    pair<int, int> split(int p, int k) {
        if(!p) {
            return {0, 0};
        }
        push(p);
        if(size(tr[p].ls) >= k) {
            auto [x, y] = split(tr[p].ls, k);
            tr[p].ls = y;
            pull(p);
            return {x, p};
        }
        auto [x, y] = split(tr[p].rs, k - size(tr[p].ls) - 1);
        tr[p].rs = x;
        pull(p);
        return {p, y};
    }
    int merge(int x, int y) {
        if(!x || !y) {
            return x | y;
        }
        if(tr[x].pri > tr[y].pri) {
            push(x);
            tr[x].rs = merge(tr[x].rs, y);
            pull(x);
            return x;
        }
        push(y);
        tr[y].ls = merge(x, tr[y].ls);
        pull(y);
        return y;
    }
    int build(const vector<Val>& a) {
        int root = 0;
        for(const Val& v : a) {
            root = merge(root, newNode(v));
        }
        return root;
    }
    int kth(int root, int k) {
        int p = root;
        while(p) {
            push(p);
            int s = size(tr[p].ls);
            if(k == s + 1) {
                return p;
            }
            if(k <= s) {
                p = tr[p].ls;
            } else {
                k -= s + 1;
                p = tr[p].rs;
            }
        }
        return 0;
    }
    tuple<int, int, int> splitRange(int root, int l, int r) {
        auto [a, bc] = split(root, l - 1);
        auto [b, c] = split(bc, r - l + 1);
        return {a, b, c};
    }
    Info query(int& root, int l, int r) {
        auto [a, b, c] = splitRange(root, l, r);
        Info res = info(b);
        root = merge(a, merge(b, c));
        return res;
    }
    void apply(int& root, int l, int r, const Tag& tag) {
        auto [a, b, c] = splitRange(root, l, r);
        applyTag(b, tag);
        root = merge(a, merge(b, c));
    }
    void rangeReverse(int& root, int l, int r) {
        auto [a, b, c] = splitRange(root, l, r);
        applyRev(b);
        root = merge(a, merge(b, c));
    }
    int erase(int& root, int l, int r) {
        auto [a, b, c] = splitRange(root, l, r);
        root = merge(a, c);
        return b;
    }
    void insert(int& root, int pos, int mid) {
        auto [a, b] = split(root, pos);
        root = merge(merge(a, mid), b);
    }
};
