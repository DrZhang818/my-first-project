#pragma once
#include <bits/stdc++.h>
using namespace std;
vector<int> centroids(const vector<vector<int>>& g) {
    int n = int(g.size()) - 1;
    if(n <= 0) {
        return {};
    }
    vector<int> p(n + 1), sz(n + 1, 1), order{1}, ans;
    for(int i = 0; i < int(order.size()); i++) {
        int u = order[i];
        for(int v : g[u]) {
            if(v != p[u]) {
                p[v] = u, order.push_back(v);
            }
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        int u = order[i], mx = 0;
        for(int v : g[u]) {
            if(v != p[u]) {
                sz[u] += sz[v], mx = max(mx, sz[v]);
            }
        }
        mx = max(mx, n - sz[u]);
        if(mx * 2 <= n) {
            ans.push_back(u);
        }
    }
    return ans;
}
