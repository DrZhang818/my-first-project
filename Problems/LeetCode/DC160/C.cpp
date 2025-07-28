#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E15;

struct edge {
    int v;
    ll l, r;
};
struct info {
    int u;
    ll w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
class Solution {
public:
    int minTime(int n, vector<vector<int>>& e) {
        vector<vector<edge>> adj(n + 1);
        for(int i = 0; i < e.size(); i++) {
            int u = e[i][0] + 1, v = e[i][1] + 1, l = e[i][2], r = e[i][3];
            adj[u].emplace_back(v, l, r);
        }
        vector<ll> dis(n + 1, inf);
        vector<bool> vis(n + 1);
        priority_queue<info> q;
        dis[1] = 0;
        q.push({1, 0});
        while(!q.empty()) {
            auto [u, w] = q.top(); q.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v, l, r] : adj[u]) {
                if(w > r) continue;
                ll nw = max(w, l) + 1;
                if(dis[v] > nw) {
                    dis[v] = nw;
                    q.push({v, dis[v]});
                }
            }
        }
        return dis[n] < inf ? dis[n] : -1;
    }
};