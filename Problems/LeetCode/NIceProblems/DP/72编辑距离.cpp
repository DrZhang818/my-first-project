#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/edit-distance/
/*
    公共子序列DP扩展   
    题意:
        给定两个字符串S和T, 每次可以对字符串S做以下操作:
        op1: 插入一个字符
        op2: 删除一个字符
        op3: 替换一个字符
        问将S转成T的最小操作次数
    关键思考:
        状态表示:
            集合: S中1~i变为T中1~j的集合
            属性: min
            定义dp[i][j] := S中1~i变为T中1~j的方案中的最小代价
        状态计算:
            考虑s[i]与t[j]
            当s[i] == t[j]时, 问题变为S中1~i-1变为T中1~j-1的方案中的最小代价
            当s[i] != t[j]时, 考虑最后一个不同点
                即如何把s[i]变为t[j]
                若选择修改操作, 问题变为S中1~i-1变为T中1~j-1的方案中的最小代价
                若选择删除操作, 问题变为S中1~i-1变为T中1~j的方案中的最小代价
                若选择插入操作, 问题变为S中1~i变为T中1~j-1的方案中的最小代价
            为了简化逻辑, 可以先把DP表中的第一行和第一列填好
            这样就不用判断是否越界了
*/
constexpr int inf = 1000000000;
class Solution {
public:
    int minDistance(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(2, vector<int>(m + 1, inf));
        for(int i = 0; i <= m; i++){
            dp[0][i] = i;
        }
        for(int i = 1; i <= n; i++){
            auto &cur = dp[i % 2], &pre = dp[(i + 1) % 2];
            cur[0] = i;
            for(int j = 1; j <= m; j++){
                if(s[i - 1] == t[j - 1]) {
                    cur[j] = pre[j - 1];
                    continue;
                }
                cur[j] = min({pre[j - 1], pre[j], cur[j - 1]}) + 1;
            }
        }
        return dp[n % 2][m];
    }
};