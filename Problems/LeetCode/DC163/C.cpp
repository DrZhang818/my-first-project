#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {
        vector<vector<info>> adj(n);
        for(int i = 0; i < edges.size(); i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, 2 * w);
        }
        vector<int> dis(n, inf);
        dis[0] = 0;
        vector<bool> vis(n);
        priority_queue<info> q;
        q.push({0, 0});
        while(!q.empty()) {
            auto [u, _] = q.top(); q.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v, w] : adj[u]) {
                if(dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    q.push({v, dis[v]});
                }
            }
        }
        return dis[n - 1] == inf ? -1 : dis[n - 1];
    }
};