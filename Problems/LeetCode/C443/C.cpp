#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//  https://leetcode.cn/problems/longest-palindrome-after-substring-concatenation-ii/
/*
    DP || Manacher
    题意:
        给定两个字符串S和T, 你需要从S和T中分别取一个子串(可以为空)
        并把两部分拼接起来得到一个新的字符串, 新的字符串必须是个回文串
        要求计算出能够构造出的最长回文串的长度
        范围: |S|,|T|∈[1,1000]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力方法, 枚举S和T的子串并拼接验证, 时间复杂度为O(n^4)
        瓶颈在于每次枚举都是从头开始, 我们思考下能否通过DP避免指针回退
        观察合法方案的性质, 我们记从S选的子串为s, 从T选的子串为t, 拼接后得到A
        A = s + t, 因为A是回文串, 因此s的前缀必然和t的后缀有相等关系
        若|s| = |t|, 那么必有s的前缀等于t的后缀, 即s = t'
        若|s| > |t|, 那么s的前缀包含t的后缀, s剩余长度一定是个回文串
        若|s| < |t|, 那么t的后缀包含s的前缀, t剩余长度一定是个回文串
        经过初步分析性质, 我们得到了答案的三种可能形式
        那么最简单的, 我们只需要把三种情况分别求出来取个max即可
        (1)对于第一种情况, 等价于求解S和T'的LCS
        (2)对于第二种情况, 我们可以枚举回文串
            记S的某段回文串为[     [   ]  ]
                                  L  R               
            那么贪心的想, 最优解就是S[:L-1]与T的LCS
        (3)对于第三种情况, 我们可以把S和T翻转, 
            这样只需要对T'和S'在再做一次情况(2)就能得到答案了
        现在的问题是如何求出S和T'的LCS以及S[:i]与T'的LCS
        这可以用经典的动态规划解决
        定义dp[i][j] := S中以i结尾, T中以j开头的最长公共子串
        若S[i] = T[j], 问题转化为1 + dp[i-1][j+1]
        若S[i] != T[j], 则答案就是0
        而S[:i]与T'的LCS就是max{dp[i][1:m]}
        第二个问题是如何枚举回文串, 由于数据量较小, 可以使用最方便的中心扩展法
        具体实现看代码细节, 枚举时i指针从1到2n-1, 把奇偶回文中心合并在一起考虑
*/
class Solution {
public:
    int longestPalindrome(string s, string t) {
        s = "@" + s;
        t = "@" + t;
        s += "#", t += "#";
        auto work = [&](string &S, string &T) -> int {
            int n = S.size() - 2, m = T.size() - 2;
            vector lcs(n + 2, vector<int>(m + 2));
            vector<int> mx(n + 2);
            int res = 0;
            for(int i = 1; i <= n; i++) {
                for(int j = m; j >= 1; j--) {
                    if(S[i] == T[j]) {
                        lcs[i][j] = lcs[i - 1][j + 1] + 1;
                    } 
                }
                mx[i] = *max_element(lcs[i].begin() + 1, lcs[i].end() - 1);
                res = max(res, mx[i] * 2);
            }
            for(int i = 1; i <= 2 * n - 1; i++) {
                int l = (i + 1) / 2, r = 1 + i / 2;
                while(S[l] == S[r]) l--, r++;
                if(l + 1 <= r - 1) res = max(res, r - l - 1 + 2 * mx[l]);
            }
            return res;
        };
        int ans = work(s, t);
        reverse(s.begin(), s.end());
        reverse(t.begin(), t.end());
        ans = max(ans, work(t, s));
        return ans;
    }
};