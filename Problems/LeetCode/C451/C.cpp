#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int maxProfit(int n, vector<int>& c, vector<int>& w, vector<vector<int>>& h, int k) {
        vector<vector<int>> adj(n + 1);
        c.insert(c.begin(), 0);
        w.insert(w.begin(), 0);
        for(int i = 0; i < h.size(); i++) {
            adj[h[i][0]].push_back(h[i][1]);
        }
        auto dfs = [&](this auto&&self, int u) -> vector<array<int,2>> {
            vector<array<int,2>> dp(k + 1);
            for(int v : adj[u]) {
                auto fv = self(v);
                for(int i = k; i >= 0; i--) {
                    for(int j = 0; j <= i; j++) {
                        dp[i][0] = max(dp[i][0], dp[i - j][0] + fv[j][0]);
                        dp[i][1] = max(dp[i][1], dp[i - j][1] + fv[j][1]);
                    }
                }
            }
            vector<array<int,2>> ndp(k + 1);
            for(int i = 0; i <= k; i++) {
                for(int j = 0; j <= 1; j++) {
                    int cost = c[u] / (j + 1);
                    if(i >= cost) {
                        ndp[i][j] = max(dp[i][0], dp[i - cost][1] + w[u] - cost);
                    } else {
                        ndp[i][j] = dp[i][0];
                    }
                }
            }
            return ndp;
        };
        return dfs(1)[k][0];
    }
};