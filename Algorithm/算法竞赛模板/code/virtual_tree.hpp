#pragma once
#include <bits/stdc++.h>
using namespace std;
struct LCA {
    int n, log;
    vector<int> depth, tin, tout, parent, order;
    vector<vector<int>> up;
    LCA(const vector<vector<int>>& g, int root = 1)
        : n(int(g.size()) - 1), log(1), depth(n + 1), tin(n + 1), tout(n + 1),
          parent(n + 1) {
        while((1LL << log) <= n) {
            log++;
        }
        up.assign(log, vector<int>(n + 1));
        if(!n) {
            return;
        }
        vector<int> stk{root}, sz(n + 1, 1);
        while(!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            tin[u] = order.size();
            order.push_back(u);
            up[0][u] = parent[u];
            for(int j = 1; j < log; j++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
            for(int i = int(g[u].size()) - 1; i >= 0; i--) {
                int v = g[u][i];
                if(v == parent[u]) {
                    continue;
                }
                parent[v] = u;
                depth[v] = depth[u] + 1;
                stk.push_back(v);
            }
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int u = order[i];
            tout[u] = tin[u] + sz[u];
            if(parent[u]) {
                sz[parent[u]] += sz[u];
            }
        }
    }
    bool isAnc(int u, int v) const {
        return tin[u] <= tin[v] && tin[v] < tout[u];
    }
    int jump(int u, int k) const {
        if(k > depth[u]) {
            return 0;
        }
        for(int j = 0; j < log; j++) {
            if(k >> j & 1) {
                u = up[j][u];
            }
        }
        return u;
    }
    int lca(int u, int v) const {
        if(depth[u] < depth[v]) {
            swap(u, v);
        }
        u = jump(u, depth[u] - depth[v]);
        if(u == v) {
            return u;
        }
        for(int j = log - 1; j >= 0; j--) {
            if(up[j][u] != up[j][v]) {
                u = up[j][u], v = up[j][v];
            }
        }
        return parent[u];
    }
    int dis(int u, int v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

struct VirtualTree : LCA {
    VirtualTree(const vector<vector<int>>& adj, int root = 1) : LCA(adj, root) {
    }
    pair<int, vector<pair<int, int>>> build(vector<int> nodes) const {
        if(nodes.empty()) {
            return {0, {}};
        }
        auto cmp = [&](int u, int v) { return tin[u] < tin[v]; };
        sort(nodes.begin(), nodes.end(), cmp);
        int k = int(nodes.size());
        for(int i = 1; i < k; i++) {
            nodes.push_back(lca(nodes[i - 1], nodes[i]));
        }
        sort(nodes.begin(), nodes.end(), cmp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> edges;
        vector<int> st;
        for(int u : nodes) {
            while(!st.empty() && lca(st.back(), u) != st.back()) {
                st.pop_back();
            }
            if(!st.empty()) {
                edges.push_back({st.back(), u});
            }
            st.push_back(u);
        }
        return {nodes.front(), edges};
    }
};