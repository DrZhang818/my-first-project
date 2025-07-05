#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/count-substrings-divisible-by-last-digit/description/
/*  
    合法子序列(子串)DP
    题意:
        给你一个只包含数字的字符串, 请你返回s的最后一位不是0的子字符串中, 可以被子字符串
        最后一位整除的数目
        注意: 子字符串可以有前导0
    关键思考:
        计数类题目常用算法: 组合数学 || DP
        对于本题来说, 组合数学需要针对0~9每个数字单独做分类讨论, 显然非常麻烦, 并且需要很多数论知识
        于是尝试设计DP来解决问题
        由于是子串问题, 因此每个位置i与它的上一位i-1之前一定有很强的关联性
        因此很自然的想法就是把i作为一个状态参数
        考虑对于每个i, 计算以s[i]结尾的合法子字符串数量
        这里定义一个字符串是合法的, 当且仅当它能被最后一位整除
        首先如果s[i]是'0', 由题意一定是不合法
        对于其他的数, s[i]本身一定是合法的, 因为x % x == 0恒成立
        那么问题就转化为以i-1结尾的子字符串中, 有多少个添加了s[i]后能够被s[i]整除
        由于涉及到整除, 因此另一个状态也就呼之欲出: 模数
        此时的dp[i][mod]能够实现状态转移吗?
        显然是不行, 因为这里还涉及到"能够被s[i]整除", 因此我们不仅要知道模数, 还要知道它是谁的模数
        从而我们设计出了本题的三个DP状态: dp[i][x][m] := 以i结尾的子字符串中, 模x余m的数量
        接下来考虑如何进行状态转移
        例如我们对于"...93", 我们知道了模3余0的个数
        如何转移到"...936"模3余0呢?
        对于取模这种复杂运算, 查表法难以进行, 我们思考下刷表法
        也就是思考dp[i][3][0]能转移到哪里
        设以i结尾的某个字符串数值为num
        那么转移到i + 1就是num * 10 + x, 这个数模m的余数是(num * 10 + x) % m
        而根据模运算, 这个余数可以写为(num % m * 10 + x) % m
        而num % m的个数正是dp[i][m][num % m]
        我们记rem = num % m
        那么dp[i + 1][m][(res * 10 + x) % m]的个数就可以由dp[i][m][res]转移而得
        最后如何统计答案?
        对于每个位置, 答案加上dp[i][s[i]][0]即可
*/
class Solution {
public:
    ll countSubstrings(string s) {
        vector<vector<ll>> dp(10, vector<ll>(10, 0));
        int n = s.size();
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            int x = s[i] - '0';
            for(int m = 1; m <= 9; m++) {
                vector<ll> ndp(10);
                ndp[x % m] = 1;
                for(int res = 0; res < m; res++) {
                    ndp[(res * 10 + x) % m] += dp[m][res];
                }
                dp[m] = ndp;
            }
            ans += dp[x][0];
        }
        return ans;
    }
};