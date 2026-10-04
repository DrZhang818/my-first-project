#pragma once
#include <bits/stdc++.h>
using namespace std;
struct NextDSU {
    vector<int> fa;
    NextDSU(int n = 0) : fa(n + 2) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        int r = x;
        while(r != fa[r]) {
            r = fa[r];
        }
        while(x != r) {
            int y = fa[x];
            fa[x] = r;
            x = y;
        }
        return r;
    }
    int next(int x) {
        return find(x);
    }
    void erase(int x) {
        fa[x] = find(x + 1);
    }
};
