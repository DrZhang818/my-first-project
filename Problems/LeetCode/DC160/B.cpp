#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

class Solution {
public:
    ll minCost(int n, int m, vector<vector<int>>& c) {
        vector dp(n + 1, vector<ll>(m + 1, inf));
        for(int i = 0; i <= n; i++) dp[i][0] = 0;
        for(int j = 0; j <= m; j++) dp[0][j] = 0;
        dp[1][1] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + i * j + c[i - 1][j - 1];
            }
        }
        return dp[n][m] - c[n - 1][m - 1];
    }
};