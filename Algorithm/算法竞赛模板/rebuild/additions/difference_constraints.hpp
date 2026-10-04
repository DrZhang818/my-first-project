#include <bits/stdc++.h>
using namespace std;
struct DifferenceConstraints {
    using i64 = long long;
    using i128 = __int128_t;
    struct Edge {
        int u, v;
        i64 w;
    };
    int n;
    vector<Edge> edges;
    vector<vector<int>> g;
    DifferenceConstraints(int n_) : n(n_), g(n_ + 1) {
    }
    // x[v] - x[u] <= w
    void le(int u, int v, i64 w) {
        g[u].push_back(edges.size());
        edges.push_back({u, v, w});
    }
    void eq(int u, int v, i64 w) {
        assert(w != LLONG_MIN);
        le(u, v, w);
        le(v, u, -w);
    }
    bool solve(vector<i128>& d, bool queueMode = true) const {
        d.assign(n + 1, 0); // Implicit super source to every vertex.
        if(!queueMode) {
            for(int round = 1; round <= n; round++) {
                bool changed = false;
                for(auto [u, v, w] : edges) {
                    if(d[v] > d[u] + w) {
                        d[v] = d[u] + w;
                        changed = true;
                        if(round == n) {
                            return false;
                        }
                    }
                }
                if(!changed) {
                    break;
                }
            }
            return true;
        }
        queue<int> q;
        vector<bool> in(n + 1, true);
        vector<int> len(n + 1);
        for(int u = 1; u <= n; u++) {
            q.push(u);
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            in[u] = false;
            for(int id : g[u]) {
                auto [from, v, w] = edges[id];
                if(d[v] <= d[u] + w) {
                    continue;
                }
                d[v] = d[u] + w;
                len[v] = len[u] + 1;
                if(len[v] >= n) {
                    return false;
                }
                if(!in[v]) {
                    in[v] = true, q.push(v);
                }
            }
        }
        return true;
    }
};
