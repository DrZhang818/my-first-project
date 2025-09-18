#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

class Solution {
public:
    int uniquePaths(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        vector dp(n + 1, vector<array<int,2>>(m + 1, {0, 0}));
        dp[n - 1][m - 1][0] = dp[n - 1][m - 1][1] = 1;
        for(int i = n - 1; i >= 0; i--) {
            for(int j = m - 1; j >= 0; j--) {
                if(a[i][j]) {
                    add(dp[i][j][1], dp[i][j + 1][0]);
                    add(dp[i][j][0], dp[i + 1][j][1]);
                } else {
                    add(dp[i][j][0], dp[i][j + 1][0]);
                    add(dp[i][j][0], dp[i + 1][j][1]);
                    add(dp[i][j][1], dp[i][j + 1][0]);
                    add(dp[i][j][1], dp[i + 1][j][1]);
                }
            }
        }
        return dp[0][0][0];
    }
};