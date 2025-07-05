#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/distinct-subsequences/description/
/*
    多维DP
    题意:
        给定两个字符串S和T, 要求计算出S的子序列中与T相等的个数
        结果对1e9 + 7取模
    关键思考:
        状态表示:
            集合: S中1~i的所有子序列中等于T中前j个字符形成的子串
            属性: 个数
            定义dp[i][j] := S中1~i的所有子序列中等于T中前j个字符形成的子串的个数
        状态计算:
            找最后一个不同点
            可以把S中1~i的所有子序列划分为:
                S中不包含s[i]的所有子序列和S中包含s[i]的所有子序列
            (1)不包含s[i]的所有子序列
                问题转化成S中1~i-1的所有子序列中等于T中前j个字符形成的子串的个数
            (2)包含s[i]的所有子序列
                如果s[i] != t[j] 这种方案一定是不合法的, 因为最后一个字符不同, 整个串必然不同
                如果s[i] == t[j], 问题转化成S中1~i-1的所有子序列中等于T中前j-1个字符形成的子串的个数
            因此转移方程就是
                dp[i][j] = dp[i-1][j] + (s[i] == t[j] ? dp[i-1][j-1] : 0)
*/
constexpr int MOD = 1e9 + 7;
class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<int> dp(m + 1, 0);
        dp[0] = 1;
        for(int i = 1; i <= n; i++){
            for(int j = m; j >= 1; j--){
                if(s[i - 1] == t[j - 1]){
                    dp[j] = (dp[j] + dp[j - 1]) % MOD;
                }
            }
        }
        return dp[m];
    }
};