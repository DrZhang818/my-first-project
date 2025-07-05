#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/the-number-of-good-subsets/description/
/*
    值域状压DP 
    题意:
        给定一个长度为n的数组, 你需要计算数组包含的合法子序列个数
        一个子序列是合法的, 当且仅当所有元素的乘积可以表示为互不相同的质数的乘积
        结果对1e9 + 7取模
        范围: n∈[1,1e5], a[i]∈[1,30]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力 -> DP || 数学, 常用优化方法为: 前缀和 || 二分 || 双指针 || 分块
        分析题目, 我们发现以下性质:
        (1)数字1本身不能作为子序列, 但可以在参与到其他子序列当中, 并且出现次数任意
           因此根据乘法原理, ans = 不含1的合法子序列个数 × 2^c1
        (2)除1之外的任何数字, 在同一个子序列中最多只能出现1次
           这提示我们可以利用分块思想计算相同贡献, 即x提供的贡献 = cntx × 包含1个x的合法子序列个数
        由于a[i]范围很小, 这提示我们可以枚举每个x选或不选, 想到这里我们就要进一步思考:
        选上这个数后的数量是否可以由之前的状态转移过来
        我们考虑用二进制表示每个质数是否被选上
        定义dp[i][s] := 考虑2~i范围内的数, 当前状态为s时的合法子序列数量
        不选, 那么转移到dp[i - 1][s]
        选, 那么转移到dp[i - 1][s ^ i]
        因此状态转移方程就是dp[i][s] = dp[i - 1][s] + cnt[i] * dp[i - 1][s ^ x]
        初始状态: 可以设定dp[1][1] -> dp[1][(1 << 10) - 1]全部为2^c1, 因为只要选上至少一个质数, 状态就是2^c1
        返回值: dp[30][0]        
*/
class Solution {
    ll power_pow(ll a, ll b, ll mod){
        ll res = 1;
        a %= mod;
        while(b > 0){
            if(b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
public:
    const int MOD = 1e9 + 7;
    vector<int> primes{2,3,5,7,11,13,17,19,23,29};
    int numberOfGoodSubsets(vector<int>& nums) {
        vector<int> s(31);
        for(int i = 2; i <= 30; i++) {
            int x = i;
            for(int j = 0; j < primes.size(); j++) {
                if(x % primes[j] == 0) {
                    s[i] |= (1 << j);
                    x /= primes[j];
                    if(x % primes[j] == 0) {
                        s[i] = 0;
                        break;
                    }
                }
            }
        }
        int c1 = 0;
        vector<int> a;
        unordered_map<int,int> mp;
        a.reserve(nums.size());
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != 1) {
                a.push_back(nums[i]);
                mp[nums[i]]++;
            } else {
                c1++;
            }
        }
        int n = a.size();
        if(n == 0) return 0;
        vector<int> dp(1 << 10);
        ll fac = power_pow(2LL, c1, MOD);
        for(int s = 1; s < 1 << 10; s++) {
            dp[s] = fac;
        }
        for(int i = 2; i <= 30; i++) {
            if(s[i] == 0 || mp[i] == 0) continue;
            for(int msk = (1 << 10) - 1; msk >= 0; msk--) {
                int x = s[i];
                if(x && (msk & x) == 0) {
                    dp[msk] = (dp[msk] + (ll)mp[i] * dp[msk ^ x] % MOD) % MOD;
                }
            }
        }
        return dp[0];
    }
};