#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/description/
class Solution {
public:
    int maximumSum(vector<int>& a) {
        int n = a.size();
        vector<array<int,2>> dp(n + 1);
        dp[0][0] = a[0], dp[0][1] = -inf;
        for(int i = 1; i < n; i++) {
            dp[i][0] = max(0, dp[i - 1][0]) + a[i];
            dp[i][1] = max(dp[i - 1][1] + a[i], dp[i - 1][0]);
        }
        int ans = -inf;
        for(int i = 0; i < n; i++) {
            ans = max(ans, dp[i][0]);
            ans = max(ans, dp[i][1]);
        }
        return ans;
    }
};