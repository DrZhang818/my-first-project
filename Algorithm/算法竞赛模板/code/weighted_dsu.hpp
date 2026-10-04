#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <class T = i64> struct WeightDSU {
    vector<int> fa, sz;
    vector<T> d;
    int cnt;
    WeightDSU(int n = 0) : fa(n + 1), sz(n + 1, 1), d(n + 1), cnt(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if(x == fa[x]) {
            return x;
        }
        int y = fa[x];
        fa[x] = find(y);
        d[x] += d[y];
        return fa[x];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int groups() const {
        return cnt;
    }
    T diff(int x, int y) {
        int a = find(x);
        int b = find(y);
        assert(a == b);
        return d[y] - d[x];
    }
    // value[y] - value[x] = w
    bool merge(int x, int y, T w) {
        int a = find(x);
        int b = find(y);
        if(a == b) {
            return d[y] - d[x] == w;
        }
        T t = w + d[x] - d[y];
        if(sz[a] >= sz[b]) {
            fa[b] = a;
            d[b] = t;
            sz[a] += sz[b];
        } else {
            fa[a] = b;
            d[a] = -t;
            sz[b] += sz[a];
        }
        cnt--;
        return true;
    }
};
