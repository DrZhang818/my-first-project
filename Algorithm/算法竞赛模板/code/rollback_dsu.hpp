#pragma once
#include <bits/stdc++.h>
using namespace std;
struct UndoDSU {
    vector<int> fa, sz;
    vector<array<int, 3>> his;
    int cnt;
    UndoDSU(int n = 0) : fa(n + 1), sz(n + 1, 1), cnt(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) const {
        while(x != fa[x]) {
            x = fa[x];
        }
        return x;
    }
    bool same(int x, int y) const {
        return find(x) == find(y);
    }
    int size(int x) const {
        return sz[find(x)];
    }
    int groups() const {
        return cnt;
    }
    int snapshot() const {
        return int(his.size());
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
        his.push_back({x, y, sz[x]});
        fa[y] = x;
        sz[x] += sz[y];
        cnt--;
        return true;
    }
    void rollback(int t) {
        while(int(his.size()) > t) {
            auto [x, y, oldSize] = his.back();
            his.pop_back();
            fa[y] = y;
            sz[x] = oldSize;
            cnt++;
        }
    }
};
