#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& e, string t) {
        vector<vector<int>> adj(n);
        vector dp(n, vector(n, vector<int>(1 << n)));
        for(int i = 0; i < e.size(); i++) {
            int u = e[i][0], v = e[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        auto dfs = [&](this auto &&self, int i, int j, int s) -> int {
            int &res = dp[i][j][s];
            if(res) return res;
            int w = i == j ? 1 : 2;
            res = w;
            for(int u : adj[i]) {
                if(s >> u & 1) continue;
                for(int v : adj[j]) {
                    if(s >> v & 1 || u == v || t[u] != t[v]) continue;
                    if(u > v) swap(u, v);
                    res = max(res, w + self(u, v, s | 1 << u | 1 << v));
                }
            }
            return res;
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans = max(ans, dfs(i, i, 1 << i));
        }
        for(int i = 0; i < e.size(); i++) {
            int u = e[i][0], v = e[i][1];
            if(t[u] == t[v]) {
                if(u > v) swap(u, v);
                ans = max(ans, dfs(u, v, 1 << u | 1 << v));
            }
        }
        return ans;
    }
};