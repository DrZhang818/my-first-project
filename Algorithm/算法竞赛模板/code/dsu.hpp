#pragma once
#include <bits/stdc++.h>
using namespace std;
struct DSU {
    vector<int> fa, sz;
    int cnt;
    DSU(int n = 0) : fa(n + 1), sz(n + 1, 1), cnt(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        if(sz[x] < sz[y]) {
            swap(x, y);
        }
        fa[y] = x;
        sz[x] += sz[y];
        cnt--;
        return true;
    }
    int size(int x) {
        return sz[find(x)];
    }
    int groups() const {
        return cnt;
    }
};
