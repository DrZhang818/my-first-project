#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/number-of-ways-to-select-buildings/description/
/*
    DP
    题意:
        给定一个长度为n的01字符串S, 定义一个子序列是合法的, 当且仅当任意相邻两项不相等
        要求计算出字符串S的合法子序列个数
        范围: n∈[3,1e5]
    关键思考:
        本题是计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力方法, 枚举所有长度为3的子序列并逐一验证, 时间复杂度为3*C[n][3] = O(n^3)
        优化的关键在于如何把多次贡献一份变成一次贡献多份
        我们可以考虑定义dp[i][j][s] := 前i个数字, 长度为j且结尾状态为s的合法子序列个数
        那么状态转移很容易得到:
            即第i个数状态为x, 则有
            dp[i][1][x] = dp[i - 1][1][x] + 1
            dp[i][j][x] = dp[i - 1][j - 1][x ^ 1] + dp[i - 1][j][x]
            dp[i][j][x ^ 1] = dp[i - 1][j][x ^ 1]
        对于本题来说, 由于长度为3, 所以只需用几个变量即可完成转移, 而无需开三维数组
*/
class Solution {
public:
    ll numberOfWays(string s) {
        ll dp0 = 0, dp1 = 0, c0 = 0, c1 = 0;
        ll ans = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') {
                c0 += 1;
                dp1 += c1;
                ans += dp0;
            } else {
                c1 += 1;
                dp0 += c0;
                ans += dp1;
            }
        }  
        return ans;
    }
};

//扩展到k的解法:
    
class Solution {
public:
    ll numberOfWays(string s, int k = 3) {
        vector dp(k + 1, vector<ll>(2, 0));
        for(int i = 0; i < s.size(); i++) {
            int x = s[i] - '0';
            dp[1][x] += 1;
            for(int j = 1; j <= k; j++) {
                dp[j][x] += dp[j - 1][x ^ 1];
            }
        }
        return dp[k][0] + dp[k][1];
    }
};