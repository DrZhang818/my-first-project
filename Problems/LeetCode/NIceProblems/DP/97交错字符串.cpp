#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/interleaving-string/
/*
    最长公共子序列DP(LCS)
    题意:
        给定三个字符串s1,s2,s3, 验证s3是否可以由s1和s2交错组成
    关键思考:
        状态表示:
            集合: s1前i个字符, s2前j个字符组成s3前i+j个字符的集合
            属性: 布尔值
            定义: dp[i][j] := s1前i个字符, s2前j个字符能否组成s3前i+j个字符
        状态计算:
            寻找最后一个不同点: s3第i+j个字符的来源
            来源于s1(必须有s1[i - 1] == s3[i + j - 1]):
                问题变成s1前i - 1个字符, s2前j个字符能否组成s3前i+j-1个字符
            来源于s2(必须有s2[j - 1] == s3[i + j - 1]):
                问题变成s1前i个字符, s2前j - 1个字符能否组成s3前i+j-1个字符
            最后二者有一个满足条件即是true 
*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int n = s1.size(), m = s2.size();
        if(n + m != s3.size()) return false;
        vector<int> dp(m + 1, false);
        dp[0] = true;
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= m; j++){
                if(i > 0) dp[j] = (dp[j] && s1[i - 1] == s3[i + j - 1]);
                if(j > 0) dp[j] |= (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
            }
        }
        return dp[m];
    }
};