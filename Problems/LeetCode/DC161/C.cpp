#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;

struct info {
    int v;
    ll w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& e, vector<bool>& tag, ll k) {
        int n = tag.size();
        vector<vector<info>> adj(n);
        vector<int> deg(n);
        for(int i = 0; i < e.size(); i++) {
            int u = e[i][0], v = e[i][1], w = e[i][2];
            if(!tag[u] || !tag[v]) continue;
            adj[u].emplace_back(v, w);
            deg[v]++;
        }
        queue<int> q;
        for(int i = 1; i < n; i++) {
            if(deg[i] == 0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(auto [v, _] : adj[u]) {
                if(--deg[v] == 0 && v) {
                    q.push(v);
                }
            }
        }
        auto ck = [&](int x) -> bool {
            vector<ll> dis(n, inf);
            dis[0] = 0;
            auto d = deg;
            queue<int> q;
            q.push(0);
            while(!q.empty()) {
                int u = q.front(); q.pop();
                if(u == n - 1) return dis[u] <= k;
                for(auto [v, w] : adj[u]) {
                    if(--d[v] == 0) q.push(v);
                    if(w < x) continue;
                    dis[v] = min(dis[v], dis[u] + w);
                }
            }
            return false;
        };
        int l = -1, r = 1000000007;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid)) {
                l = mid;
            } else {
                r = mid;
            }
        }
        return l;
    }
};