#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/solving-questions-with-brainpower/submissions/648002347/
class Solution {
public:
    ll mostPoints(vector<vector<int>>& a) {
        int n = a.size();
        vector<ll> dp(n + 1);
        dp[n - 1] = a[n - 1][0];
        for(int i = n - 2; i >= 0; i--) {
            dp[i] = max(dp[i + 1], dp[min(n, i + 1 + a[i][1])] + a[i][0]);
        }
        return dp[0];
    }
};