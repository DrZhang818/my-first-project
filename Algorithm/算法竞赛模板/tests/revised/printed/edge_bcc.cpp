#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using i64 = long long;
using namespace std;
struct Lowlink {
    int n, timer = 0;
    vector<pair<int, int>> edges;
    vector<vector<pair<int, int>>> adj;
    vector<int> dfn, low;
    vector<bool> bridge, cut;
    Lowlink(int n_ = 0)
        : n(n_), edges(1), adj(n_ + 1), dfn(n_ + 1), low(n_ + 1), cut(n_ + 1) {
    }
    int addEdge(int u, int v) {
        int id = int(edges.size());
        edges.push_back({u, v});
        adj[u].push_back({v, id});
        adj[v].push_back({u, id});
        return id;
    }
    void work() {
        bridge.assign(edges.size(), false);
        for(int u = 1; u <= n; u++) {
            if(!dfn[u]) {
                dfs(u, 0);
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
                    dfn[v] = low[v] = ++timer;
                    cs.push_back({v, id, 0, 0});
                } else {
                    low[u] = min(low[u], dfn[v]);
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
                if(low[u] > dfn[p]) {
                    bridge[pe] = true;
                }
                if(cs.back()[1] && low[u] >= dfn[p]) {
                    cut[p] = true;
                }
            }
        }
    }
};
struct EdgeBCC {
    Lowlink bridge;
    vector<int> id;
    vector<vector<int>> comp;
    EdgeBCC(int n = 0) : bridge(n), id(n + 1), comp(1) {
    }
    int addEdge(int u, int v) {
        return bridge.addEdge(u, v);
    }
    void work() {
        bridge.work();
        for(int s = 1; s <= bridge.n; s++) {
            if(id[s] != 0) {
                continue;
            }
            int bel = int(comp.size());
            comp.push_back({});
            vector<int> stack{s};
            id[s] = bel;
            while(!stack.empty()) {
                int u = stack.back();
                stack.pop_back();
                comp.back().push_back(u);
                for(auto [v, edge] : bridge.adj[u]) {
                    if(!bridge.bridge[edge] && id[v] == 0) {
                        id[v] = bel;
                        stack.push_back(v);
                    }
                }
            }
        }
    }
};
