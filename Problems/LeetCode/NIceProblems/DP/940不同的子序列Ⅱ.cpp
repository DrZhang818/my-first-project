#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/distinct-subsequences-ii/
/*  
    特殊子序列DP || 前缀和优化
    题意:
        给定一个字符串s, 要求计算出s的不同非空子序列的个数, 结果对1e9+7取模
    关键思考:
        状态表示:
            集合: 所有1~i中以s[i]结尾的不同非空子序列的集合
            属性: 个数
            定义dp[s[i]] := 所有1~i中以s[i]结尾的不同非空子序列的个数
        状态计算:
            目标是计算1~i中以s[i]结尾的子序列个数
            那么s[i]已经固定, 就是看s[i]前面的总个数
            可以枚举前一位(子序列倒数第二位)放哪个元素
            具体来说是看这一位放'a'->'z'时的个数, 由于倒数第二位不同, 因此天然具有去重性质
            那么转移方程就是dp[s[i]] = ∑dp + 1
            这样每次转移就需要遍历26个字母的状态即可
            由于一直利用累加和, 因此考虑使用前缀和优化
            使用变量tot实时记录∑dp的值, 即可做到一次转移
            因此
                令pre = dp[s[i]]
                dp[s[i]] = tot + 1
                tot = tot - pre + dp[s[i]]
                即tot = 2 * tot + 1 - pre
*/
const int MOD = 1e9 + 7;
class Solution {
public:
    int distinctSubseqII(string s) {
        vector<ll> dp(26);
        ll tot = 0;
        for(char c : s){
            int cur = c - 'a';
            ll temp = dp[cur];
            dp[cur] = (tot + 1 + MOD) % MOD;
            tot = (2 * tot + 1 - temp + MOD) % MOD;
        }
        return tot;
    }
};