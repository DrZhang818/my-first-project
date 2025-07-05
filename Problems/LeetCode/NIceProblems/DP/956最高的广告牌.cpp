#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/tallest-billboard/
/*
    01背包扩展
    

*/
constexpr int inf = 1000000000;
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        int n = rods.size();
        ll mx = 0;
        for(int i = 0; i < n; i++){
            mx += rods[i];
        }
        vector<vector<int>> dp(2, vector<int>(mx + 1, -inf));
        dp[1][0] = 0;
        for(int i = 0; i < n; i++){
            int x = rods[i];
            for(int j = 0; j <= mx; j++){
                dp[i%2][j] = max(dp[(i+1)%2][j], dp[(i+1)%2][abs(j - x)] + x); 
                if(j + x <= mx) dp[i%2][j] = max(dp[i%2][j], dp[(i+1)%2][j + x] + x);
            }
        }
        return dp[(n+1)%2][0] / 2;
    }
};