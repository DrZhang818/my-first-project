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
    int maxWeight(int n, vector<vector<int>>& e, int k, int t) {
        int m = e.size();
        vector<vector<info>> adj(n + 1);
        for(int i = 0; i < m; i++) {
            int u = e[i][0], v = e[i][1], w = e[i][2];
            adj[u + 1].push_back({v + 1, w});
        }
        for(int i = 1; i <= n; i++) {
            adj[0].push_back({i, 0});
        }
        k += 1;
        vector memo(n + 1, vector<vector<int>>(k + 1, vector<int>(t + 1, -2)));
        auto dfs = [&](this auto &&self, int u, int len, int w) -> int {
            if(len == k) return 0;
            int &res = memo[u][len][w];
            if(res != -2) return res;
            res = -1;
            for(auto [v, nw] : adj[u]) {
                if(w + nw >= t) continue;
                res = max(res, self(v, len + 1, w + nw) + nw);
            }
            return res;
        };
        int ans = dfs(0, 0, 0);
        return ans;
    }
};