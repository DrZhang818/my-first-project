#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e17;


class Solution {
public:
    ll subtreeInversionSum(vector<vector<int>>& e, vector<int>& a, int k) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector<vector<int>> adj(n + 1); 
        for(int i = 0; i < n - 1; i++) {
            int u = e[i][0] + 1, v = e[i][1] + 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector memo(n + 1, vector<vector<ll>>(k + 1, vector<ll>(2, -inf)));
        auto dfs = [&](this auto &&self, int u, int fa, int lim, int tag) -> ll { 
            ll &res = memo[u][lim][tag];
            if(res != -inf) return res;
            ll cur = 0, t = (tag == 0 ? a[u] : -a[u]);
            if(lim != 0) {
                cur = t;
                for(int v : adj[u]) {
                    if(v == fa) continue;
                    cur += self(v, u, lim - 1, tag);
                }
                res = cur;
            } else {
                ll c1 = t, c2 = -t;
                for(int v : adj[u]) {
                    if(v == fa) continue;
                    c1 += self(v, u, 0, tag);
                    c2 += self(v, u, k - 1, tag ^ 1);
                }
                res = max(c1, c2);
            }
            return res;
        };
        return dfs(1, 0, 0, 0);
    }
};