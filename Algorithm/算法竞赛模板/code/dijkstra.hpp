#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Dijkstra {
    struct Edge {
        int to;
        i64 w;
    };
    static constexpr i64 inf = numeric_limits<i64>::max() / 4;
    vector<vector<Edge>> adj;
    Dijkstra(int n = 0) : adj(n + 1) {
    }
    void addEdge(int u, int v, i64 w) {
        adj[u].push_back({v, w});
    }
    vector<i64> run(int s) const {
        vector<i64> dis(adj.size(), inf);
        priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;
        dis[s] = 0;
        q.push({0, s});
        while(!q.empty()) {
            auto [du, u] = q.top();
            q.pop();
            if(du != dis[u]) {
                continue;
            }
            for(auto [v, w] : adj[u]) {
                if(dis[v] > du + w) {
                    dis[v] = du + w;
                    q.push({dis[v], v});
                }
            }
        }
        return dis;
    }
};
