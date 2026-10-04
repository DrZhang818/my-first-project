#include <bits/stdc++.h>
using namespace std;
struct EulerTrail {
    // dir=true: directed; dir=false: undirected. Vertices are 1..n.
    static bool solve(int n, const vector<pair<int, int>>& e, bool dir, vector<int>& ans) {
        ans.clear();
        if(!n) {
            return e.empty();
        }
        vector<vector<pair<int, int>>> g(n + 1);
        vector<int> in(n + 1), out(n + 1), it(n + 1);
        for(int i = 0; i < int(e.size()); i++) {
            auto [u, v] = e[i];
            g[u].push_back({v, i});
            ++out[u];
            ++in[v];
            if(!dir) {
                g[v].push_back({u, i}), ++out[v], ++in[u];
            }
        }
        int s = 1, plus = 0, minus = 0, odd = 0;
        for(int u = 1; u <= n; u++) {
            if(out[u]) {
                s = u;
                break;
            }
        }
        for(int u = 1; u <= n; u++) {
            if(dir) {
                int d = out[u] - in[u];
                if(abs(d) > 1) {
                    return false;
                }
                if(d == 1) {
                    ++plus, s = u;
                }
                if(d == -1) {
                    ++minus;
                }
            } else if(out[u] & 1) {
                ++odd, s = u;
            }
        }
        if(dir && !((plus == 0 && minus == 0) || (plus == 1 && minus == 1))) {
            return false;
        }
        if(!dir && odd != 0 && odd != 2) {
            return false;
        }
        vector<bool> used(e.size());
        vector<int> stk(1, s);
        while(!stk.empty()) {
            int u = stk.back();
            while(it[u] < int(g[u].size()) && used[g[u][it[u]].second]) {
                ++it[u];
            }
            if(it[u] == int(g[u].size())) {
                ans.push_back(u), stk.pop_back();
            } else {
                auto [v, id] = g[u][it[u]++];
                used[id] = true;
                stk.push_back(v);
            }
        }
        if(ans.size() != e.size() + 1) {
            ans.clear();
            return false;
        }
        reverse(ans.begin(), ans.end());
        return true;
    }
};
