#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    struct info {
        int v, w;
    };
    vector<int> minimumWeight(vector<vector<int>>& e, vector<vector<int>>& Q) {
        int n = e.size() + 1;
        vector<vector<info>> adj(n + 1);
        for(int i = 0; i < n - 1; i++) {
            int u = e[i][0], v = e[i][1], w = e[i][2];
            adj[u + 1].push_back({v + 1, w});
            adj[v + 1].push_back({u + 1, w});
        }
        vector<int> fa(n + 1), sz(n + 1), dep(n + 1), top(n + 1), son(n + 1);
        auto dfs1 = [&](this auto&&self, int u, int f) -> void {
            fa[u] = f, dep[u] = dep[f] + 1, sz[u] = 1;
            for(auto [v, _] : adj[u]) {
                if(v != f) {
                    self(v, u);
                    sz[u] += sz[v];
                    if(sz[v] > sz[son[u]]) {
                        son[u] = v;
                    }
                }
            }
        };
        dfs1(1, 0);
        auto dfs2 = [&](this auto&&self, int u, int tp) -> void {
            top[u] = tp;
            if(son[u] == 0) return ;
            self(son[u], tp);
            for(auto [v, _] : adj[u]) {
                if(v == fa[u] || v == son[u]) continue;
                self(v, v);
            }
        };  
        dfs2(1, 1);
        auto LCA = [&](int u, int v) -> int {
            while(top[u] != top[v]) {
                if(dep[top[u]] < dep[top[v]]) swap(u, v);
                u = fa[top[u]];
            }
            return dep[u] < dep[v] ? u : v;
        };
        vector<int> dis(n + 1);
        auto dfs3 = [&](this auto &&self, int u) -> void {
            for(auto [v, w] : adj[u]) {
                if(v == fa[u]) continue;
                dis[v] = dis[u] + w;
                self(v);
            }
        };
        auto cal = [&](int u, int v, int lca) {
            return dis[u] + dis[v] - 2 * dis[lca];
        };
        dfs3(1);
        int q = Q.size();
        vector<int> ans(q);
        for(int i = 0; i < q; i++) {
            int u = Q[i][0] + 1, v = Q[i][1] + 1, w = Q[i][2] + 1;
            int lca1 = LCA(u, v);
            int lca2 = LCA(u, w);
            int lca3 = LCA(v, w);
            ans[i] = cal(u, v, lca1) + cal(u, w, lca2) + cal(v, w, lca3);
            ans[i] /= 2;
        }
        return ans;
    }
};