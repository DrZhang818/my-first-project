#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct LiChao {
    using i128 = __int128;
    static constexpr i128 inf = i128(1) << 120;
    struct Line {
        i64 k = 0, b = 0;
        i128 get(i64 x) const {
            return i128(k) * x + b;
        }
    };
    struct Node {
        int ls = 0, rs = 0;
        Line line;
        bool has = false;
    };
    i64 L, R;
    vector<Node> tr;
    int root = 0;
    LiChao(i64 l, i64 r) : L(l), R(r), tr(1) {
    }
    int newNode(Line line) {
        tr.push_back({0, 0, line, true});
        return int(tr.size()) - 1;
    }
    int addLine(int p, i64 l, i64 r, Line line) {
        if(!p) {
            return newNode(line);
        }
        i64 m = l + (r - l) / 2;
        bool left = line.get(l) < tr[p].line.get(l);
        bool mid = line.get(m) < tr[p].line.get(m);
        if(mid) {
            swap(line, tr[p].line);
        }
        if(l == r) {
            return p;
        }
        if(left != mid) {
            int child = addLine(tr[p].ls, l, m, line);
            tr[p].ls = child;
        } else {
            int child = addLine(tr[p].rs, m + 1, r, line);
            tr[p].rs = child;
        }
        return p;
    }
    void addLine(i64 k, i64 b) {
        root = addLine(root, L, R, {k, b});
    }
    i128 query(int p, i64 l, i64 r, i64 x) const {
        if(!p) {
            return inf;
        }
        i128 res = tr[p].line.get(x);
        if(l == r) {
            return res;
        }
        i64 m = l + (r - l) / 2;
        if(x <= m) {
            return min(res, query(tr[p].ls, l, m, x));
        }
        return min(res, query(tr[p].rs, m + 1, r, x));
    }
    i128 query(i64 x) const {
        return query(root, L, R, x);
    }
};
