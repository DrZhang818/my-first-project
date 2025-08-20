#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();
        int mx = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                mx = max(mx, grid[i][j]);
            }
        }
        vector<int> sufmn(mx + 2, inf);
        vector<int> mn(mx + 1, inf);
        vector<int> dp(m + 1);
        for(int i = 0; i <= k; i++) {
            ranges::fill(mn, inf);
            ranges::fill(dp, inf);
            dp[1] = -grid[0][0];
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    int x = grid[i][j];
                    dp[j + 1] = min({dp[j] + x, dp[j + 1] + x, sufmn[x]});
                    mn[x] = min(mn[x], dp[j + 1]);
                }
            }
            bool ok = false;
            for(int i = mx; i >= 0; i--) {
                int x = min(sufmn[i + 1], mn[i]);
                if(sufmn[i] != x) {
                    sufmn[i] = x;
                    ok = true;
                }
            }
            if(!ok) break;
        }
        return dp[m];
    }
};