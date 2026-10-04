#pragma once
#include <bits/stdc++.h>
using namespace std;
struct SCC {
    int n, timer = 0, count = 0;
    const vector<vector<int>>& adj;
    vector<int> dfn, low, stack, id;
    vector<bool> inStack;
    vector<vector<int>> comp;
    SCC(const vector<vector<int>>& graph)
        : n(int(graph.size()) - 1), adj(graph), dfn(graph.size()), low(graph.size()),
          id(graph.size(), -1), inStack(graph.size()) {
        for(int u = 1; u <= n; u++) {
            if(!dfn[u]) {
                dfs(u);
            }
        }
    }
    void dfs(int s) {
        vector<pair<int, int>> cs{{s, 0}};
        dfn[s] = low[s] = ++timer;
        stack.push_back(s);
        inStack[s] = true;
        while(!cs.empty()) {
            int u = cs.back().first;
            int& i = cs.back().second;
            if(i < int(adj[u].size())) {
                int v = adj[u][i++];
                if(!dfn[v]) {
                    dfn[v] = low[v] = ++timer;
                    stack.push_back(v);
                    inStack[v] = true;
                    cs.push_back({v, 0});
                } else if(inStack[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            } else {
                cs.pop_back();
                if(low[u] == dfn[u]) {
                    comp.push_back({});
                    while(true) {
                        int v = stack.back();
                        stack.pop_back();
                        inStack[v] = false;
                        id[v] = count;
                        comp.back().push_back(v);
                        if(v == u) {
                            break;
                        }
                    }
                    count++;
                }
                if(!cs.empty()) {
                    int p = cs.back().first;
                    low[p] = min(low[p], low[u]);
                }
            }
        }
    }
};
