#pragma once
#include <bits/stdc++.h>
using namespace std;
struct DSUOnTree {
    const vector<vector<int>>& adj;
    vector<int> parent, size, heavy, tin, tout, euler;
    int root, timer = 0;
    DSUOnTree(const vector<vector<int>>& graph, int root_ = 1)
        : adj(graph), parent(adj.size()), size(adj.size()), heavy(adj.size()),
          tin(adj.size()), tout(adj.size()), euler(adj.size()), root(root_), timer(1) {
        if(adj.size() > 1) {
            dfsSize(root, 0);
        }
    }
    void dfsSize(int root, int p) {
        vector<int> stk{root}, order;
        parent[root] = p;
        while(!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            tin[u] = timer;
            euler[timer++] = u;
            order.push_back(u);
            for(int i = int(adj[u].size()) - 1; i >= 0; i--) {
                int v = adj[u][i];
                if(v == parent[u]) {
                    continue;
                }
                parent[v] = u;
                stk.push_back(v);
            }
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int u = order[i];
            size[u] = 1;
            for(int v : adj[u]) {
                if(v != parent[u]) {
                    size[u] += size[v];
                    if(!heavy[u] || size[v] > size[heavy[u]]) {
                        heavy[u] = v;
                    }
                }
            }
            tout[u] = tin[u] + size[u] - 1;
        }
    }
    template <class Add, class Answer> void run(Add add, Answer answer) {
        if(adj.size() <= 1) {
            return;
        }
        vector<tuple<int, int, bool>> stk{{root, 0, false}};
        while(!stk.empty()) {
            auto [u, kind, keep] = stk.back();
            stk.pop_back();
            if(kind == 0) {
                stk.push_back({u, 3, keep});
                stk.push_back({u, 2, keep});
                stk.push_back({u, 1, keep});
                if(heavy[u]) {
                    stk.push_back({heavy[u], 0, true});
                }
                for(int v : adj[u]) {
                    if(v != parent[u] && v != heavy[u]) {
                        stk.push_back({v, 0, false});
                    }
                }
            } else if(kind == 1) {
                for(int v : adj[u]) {
                    if(v != parent[u] && v != heavy[u]) {
                        for(int i = tin[v]; i <= tout[v]; i++) {
                            add(euler[i], 1);
                        }
                    }
                }
                add(u, 1);
            } else if(kind == 2) {
                answer(u);
            } else if(!keep) {
                for(int i = tin[u]; i <= tout[u]; i++) {
                    add(euler[i], -1);
                }
            }
        }
    }
};
