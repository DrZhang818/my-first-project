#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct KRT {
    struct Edge {
        int u, v;
        i64 w;
    };
    int n, tot, log;
    vector<i64> weight;
    vector<array<int, 2>> child;
    vector<int> depth, bel;
    vector<vector<int>> up;
    KRT(int n_, vector<Edge> edges) : n(n_) {
        int cap = max(2, 2 * n + 1);
        vector<int> dsu(cap), root(cap);
        iota(dsu.begin(), dsu.end(), 0);
        iota(root.begin(), root.end(), 0);
        weight.assign(cap, 0);
        child.assign(cap, {0, 0});
        auto find = [&](int x) {
            int r = x;
            while(r != dsu[r]) {
                r = dsu[r];
            }
            while(x != r) {
                int y = dsu[x];
                dsu[x] = r;
                x = y;
            }
            return r;
        };
        sort(edges.begin(), edges.end(),
             [](const auto& a, const auto& b) { return a.w < b.w; });
        tot = n;
        for(auto [u, v, w] : edges) {
            int x = find(u);
            int y = find(v);
            if(x == y) {
                continue;
            }
            int z = ++tot;
            weight[z] = w;
            child[z] = {root[x], root[y]};
            dsu[x] = dsu[y] = dsu[z] = z;
            root[z] = z;
        }
        weight.resize(tot + 1);
        child.resize(tot + 1);
        log = (32 - __builtin_clz((unsigned)max(1, tot)));
        depth.assign(tot + 1, 0);
        bel.assign(tot + 1, 0);
        up.assign(log, vector<int>(tot + 1, 0));
        for(int i = 1; i <= n; i++) {
            int r = find(i);
            if(bel[r] != 0) {
                continue;
            }
            bel[r] = r;
            vector<int> stk{r};
            while(!stk.empty()) {
                int u = stk.back();
                stk.pop_back();
                bel[u] = r;
                for(int j = 1; j < log; j++) {
                    up[j][u] = up[j - 1][up[j - 1][u]];
                }
                for(int v : child[u]) {
                    if(v) {
                        up[0][v] = u;
                        depth[v] = depth[u] + 1;
                        stk.push_back(v);
                    }
                }
            }
        }
    }
    int lca(int u, int v) const {
        if(depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for(int j = 0; j < log; j++) {
            if(d >> j & 1) {
                u = up[j][u];
            }
        }
        if(u == v) {
            return u;
        }
        for(int j = log - 1; j >= 0; j--) {
            if(up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }
        return up[0][u];
    }
    bool bottle(int u, int v, i64& ans) const {
        if(bel[u] != bel[v]) {
            return false;
        }
        if(u == v) {
            ans = 0;
            return true;
        }
        ans = weight[lca(u, v)];
        return true;
    }
};
