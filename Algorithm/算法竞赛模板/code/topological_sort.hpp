#pragma once
#include <bits/stdc++.h>
using namespace std;
vector<int> toposort(const vector<vector<int>>& adj) {
    vector<int> deg(adj.size());
    int n = int(adj.size()) - 1;
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            deg[v]++;
        }
    }
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(!deg[i]) {
            q.push(i);
        }
    }
    vector<int> order;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                q.push(v);
            }
        }
    }
    if(int(order.size()) != n) {
        return {};
    }
    return order;
}
