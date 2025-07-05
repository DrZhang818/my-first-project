#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 1000000000;
class Solution {
public:
    int maxProfit(vector<int>& a) {
        int n = a.size();
        vector dp(2, vector<vector<int>>(3, vector<int>(2, -inf)));
        for(int i = 0; i <= 2; i++) {
            dp[0][i][0] = dp[1][i][0] = 0;
        }
        for(int i = 0; i < n; i++) {
            auto &pre = dp[(i + 1) % 2], &cur = dp[i % 2];
            for(int j = 1; j <= 2; j++) {
                cur[j][0] = max(pre[j][0], pre[j][1] + a[i]);
                cur[j][1] = max(pre[j][1], pre[j - 1][0] - a[i]);
            }
        }
        return dp[(n - 1) % 2][2][0];
    }
};