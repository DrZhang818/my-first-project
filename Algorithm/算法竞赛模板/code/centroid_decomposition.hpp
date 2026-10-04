#pragma once
#include <bits/stdc++.h>
using namespace std;
struct Centroid {
    const vector<vector<int>>& adj;
    vector<int> parent, level, size, fa;
    vector<bool> blocked;
    Centroid(const vector<vector<int>>& graph)
        : adj(graph), parent(adj.size()), level(adj.size()), size(adj.size()),
          fa(adj.size()), blocked(adj.size()) {
        if(adj.size() > 1) {
            build(1, 0, 0);
        }
    }
    int getSize(int u, int p) {
        vector<int> order{u};
        fa[u] = p;
        for(int i = 0; i < int(order.size()); i++) {
            int x = order[i];
            for(int v : adj[x]) {
                if(v != fa[x] && !blocked[v]) {
                    fa[v] = x, order.push_back(v);
                }
            }
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int x = order[i];
            size[x] = 1;
            for(int v : adj[x]) {
                if(v != fa[x] && !blocked[v]) {
                    size[x] += size[v];
                }
            }
        }
        return size[u];
    }
    int getCentroid(int u, int p, int n) {
        while(true) {
            int v = 0;
            for(int x : adj[u]) {
                if(x != p && !blocked[x] && size[x] * 2 > n) {
                    v = x;
                    break;
                }
            }
            if(!v) {
                return u;
            }
            p = u;
            u = v;
        }
    }
    void build(int entry, int p, int dep) {
        int c = getCentroid(entry, 0, getSize(entry, 0));
        parent[c] = p;
        level[c] = dep;
        blocked[c] = true;
        for(int v : adj[c]) {
            if(!blocked[v]) {
                build(v, c, dep + 1);
            }
        }
    }
};
