#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/longest-valid-parentheses/
/*
    线性DP——合法子数组DP
    题意:
        给定一个由'('和')'组成的字符串, 计算最长有效子串(格式正确且连续)
        一个字符串是合法的, 当且仅当字符串可以由()嵌套或并列构成
    关键思考:
        本题属于合法子数组DP
        状态表示:
            集合: 所有以s[i]结尾的合法子串的长度组成的集合
            属性: max
            定义dp[i] := 以i结尾的所有合法子串中的最大长度
        状态计算:
            由于s[i]已经固定, 就相当于要最大化s[:i-1]的合法长度
            分类讨论:
                (1)当s[i] == '('时, dp[i] = 0
                (2)当s[i] == ')'时, 最大长度就是嵌套 + 新形成 + 并列
                    嵌套: 就是dp[i-1]的长度
                    新形成: 就是看s[i - 1 - dp[i - 1]]是否存在 || 是否是'('
                    并列: 就是看dp[i - 2 - dp[i - 1]]的值
                注: 如果没有新形成, 就代表当前的')'无法配对, 因此"新形成"是必须满足的条件
                    所谓嵌套其实就是跳过前面已经形成的最大长度, 因为这一部分不能提供'('与')'配对

*/
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n);
        for(int i = 1; i < n; i++){
            int p = i - 1 - dp[i - 1];
            if(s[i] == '(' || p < 0 || s[p] != '(') continue;
            dp[i] = dp[i - 1] + 2;
            if(p - 1 >= 0){
                dp[i] += dp[p - 1];
            }
        }
        int ans = 0;
        for(auto c : dp) ans = max(ans, c);
        return ans;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}