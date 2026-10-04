#pragma once
#include <bits/stdc++.h>
using namespace std;
struct FuncGraph {
    int n;
    vector<int> to, cycle, depth, entry, pos;
    vector<vector<int>> rings, up;
    FuncGraph(const vector<int>& next)
        : n(int(next.size()) - 1), to(next), cycle(n + 1, -1), depth(n + 1), entry(n + 1),
          pos(n + 1), up(64, next) {
        vector<int> deg(n + 1), order;
        for(int u = 1; u <= n; u++) {
            ++deg[to[u]];
        }
        queue<int> q;
        for(int u = 1; u <= n; u++) {
            if(!deg[u]) {
                q.push(u);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            if(!--deg[to[u]]) {
                q.push(to[u]);
            }
        }
        for(int u = 1; u <= n; u++) {
            if(deg[u] && cycle[u] < 0) {
                int id = rings.size(), v = u;
                rings.push_back({});
                do {
                    cycle[v] = id;
                    entry[v] = v;
                    pos[v] = rings.back().size();
                    rings.back().push_back(v);
                    v = to[v];
                } while(v != u);
            }
        }
        reverse(order.begin(), order.end());
        for(int u : order) {
            int v = to[u];
            cycle[u] = cycle[v];
            entry[u] = entry[v];
            depth[u] = depth[v] + 1;
        }
        for(int j = 1; j < 64; j++) {
            for(int u = 1; u <= n; u++) {
                up[j][u] = up[j - 1][up[j - 1][u]];
            }
        }
    }
    int jump(int u, uint64_t k) const {
        for(int j = 0; j < 64; j++) {
            if(k >> j & 1) {
                u = up[j][u];
            }
        }
        return u;
    }
    // Minimum number of directed steps from u to v; -1 if unreachable.
    long long dis(int u, int v) const {
        if(cycle[u] != cycle[v]) {
            return -1;
        }
        if(depth[v]) {
            if(depth[u] < depth[v]) {
                return -1;
            }
            int k = depth[u] - depth[v];
            return jump(u, k) == v ? k : -1;
        }
        int c = cycle[u], len = rings[c].size();
        return depth[u] + (pos[v] - pos[entry[u]] + len) % len;
    }
};
