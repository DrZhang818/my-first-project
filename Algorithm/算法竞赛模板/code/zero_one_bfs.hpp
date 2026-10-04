#pragma once
#include <bits/stdc++.h>
using namespace std;
struct BFS01 {
    struct Edge {
        int to, w;
    };
    static constexpr int inf = numeric_limits<int>::max() / 4;
    vector<vector<Edge>> adj;
    BFS01(int n = 0) : adj(n + 1) {
    }
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }
    vector<int> run(int s) const {
        vector<int> dis(adj.size(), inf);
        deque<int> q;
        dis[s] = 0;
        q.push_back(s);
        while(!q.empty()) {
            int u = q.front();
            q.pop_front();
            for(auto [v, w] : adj[u]) {
                if(dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    if(w) {
                        q.push_back(v);
                    } else {
                        q.push_front(v);
                    }
                }
            }
        }
        return dis;
    }
};
