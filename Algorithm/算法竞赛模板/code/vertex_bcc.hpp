#pragma once
#include <bits/stdc++.h>
using namespace std;
struct VertexBCC {
    int n, timer = 0;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> adj;
    vector<int> dfn, low, stk;
    vector<bool> cut;
    vector<vector<int>> comp, tree;
    VertexBCC(int n_ = 0)
        : n(n_), edges(1), adj(n_ + 1), dfn(n_ + 1), low(n_ + 1), cut(n_ + 1), comp(1) {
    }
    int addEdge(int u, int v) {
        int id = int(edges.size());
        edges.push_back({u, v});
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
        return id;
    }
    void work() {
        for(int u = 1; u <= n; u++) {
            if(dfn[u]) {
                continue;
            }
            if(adj[u].empty()) {
                dfn[u] = low[u] = ++timer;
                comp.push_back({u});
            } else {
                dfs(u, 0);
            }
        }
        tree.assign(n + comp.size(), {});
        for(int i = 1; i < int(comp.size()); i++) {
            int v = n + i;
            for(int u : comp[i]) {
                tree[u].push_back(v);
                tree[v].push_back(u);
            }
        }
    }
    void dfs(int s, int e) {
        vector<array<int, 4>> cs{{s, e, 0, 0}};
        dfn[s] = low[s] = ++timer;
        while(!cs.empty()) {
            int u = cs.back()[0], pe = cs.back()[1];
            int& i = cs.back()[2];
            if(i < int(adj[u].size())) {
                auto [v, id] = adj[u][i++];
                if(id == pe) {
                    continue;
                }
                if(!dfn[v]) {
                    cs.back()[3]++;
                    stk.push_back(id);
                    dfn[v] = low[v] = ++timer;
                    cs.push_back({v, id, 0, 0});
                } else {
                    low[u] = min(low[u], dfn[v]);
                    if(dfn[v] < dfn[u]) {
                        stk.push_back(id);
                    }
                }
            } else {
                int child = cs.back()[3];
                cs.pop_back();
                if(!pe && child > 1) {
                    cut[u] = true;
                }
                if(cs.empty()) {
                    continue;
                }
                int p = cs.back()[0];
                low[p] = min(low[p], low[u]);
                if(low[u] >= dfn[p]) {
                    if(cs.back()[1] || cs.back()[3] > 1) {
                        cut[p] = true;
                    }
                    vector<int> v;
                    while(true) {
                        int e = stk.back();
                        stk.pop_back();
                        v.push_back(edges[e].first);
                        v.push_back(edges[e].second);
                        if(e == pe) {
                            break;
                        }
                    }
                    sort(v.begin(), v.end());
                    v.erase(unique(v.begin(), v.end()), v.end());
                    comp.push_back(move(v));
                }
            }
        }
    }
};
