#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/number-of-great-partitions/
/*
    01背包 || 逆向思维 || 容斥原理
    题意:
        给定一个长为n的数组和一个整数k, 分区的定义为数组划分成两个有序的组,
        并满足每个元素恰好存在于某一个组中.
        一个分区是好的, 如果满分区中每个组的元素和都大于等于k
        要求计算出不同的好分区数目, 答案对1e9+7取模
    关键思考:
        正向进行的话, 如果采用至少型01背包的方式, 会发现处理负数的通用手段
        ————累加到dp[0]在这里不可用了, 这是因为dp[0]的转移不仅仅是简单的*2
        还需要剔除掉小于lo的部分, 这就使得不能顺利状态转移  详见错误代码

        另一种正向的思路是计算出总和为k -> s-k时的方案数再累加起来, 但显然
        这样状态数太大, 时间空间都无法接受

        因此正解是从逆向思考, 利用容斥原理计算"坏分区"的数目
        一个分区是坏的, 当且仅当存在一个分区的元素和小于k
        问题就变成至多型01背包问题, 背包容量至多为k-1求方案数
        需要注意的是, "坏分区"将分为以下两种情况
        (1)只有一组的和小于k, bad分区的数量是2 * dp[k-1],
           这是因为题目规定两个组是有序的
           即划分成[1,3][2,4]与[2,4][1,3]被认为不同
           因此我们选出的"坏组"可能是第一组的, 也可能是第二组的
           通俗地讲: 好--坏   坏--好  这样一定是不重叠的
        (2)两组的和都小于k, bad分区的数量是dp[k-1]
           这是因为选出来的和为m"坏组"作为第二组的情况已经在选出来的和为s-m"坏组"作为第一组
           中出现过了
           通俗地讲: 坏--坏   坏--坏  这样是重复计算的
        比较巧妙地一点是, 情况(2)两组的和都小于k也就意味着平均数小于k
        这样无论怎么分都会出现"坏组", 因此特判这种情况下有0个好分区
*/
constexpr int MOD = 1e9 + 7;
class Solution {
private:
    ll pow_mod(ll a, ll b){
        ll res = 1;
        while(b > 0){
            if(b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
public:
    int countPartitions(vector<int>& a, int k) {
        int n = a.size();
        ll tot = pow_mod(2, n);
        ll sum = accumulate(a.begin(), a.end(), 0LL);
        if(sum < 2 * k - 1) return 0;
        vector<ll> dp(k, 1);
        for(ll x : a){
            for(int j = k - 1; j >= x; j--){
                dp[j] = (dp[j] + dp[j - x]) % MOD;
            }
        }
        return (tot - 2 * dp[k - 1] % MOD + MOD) % MOD;
    }
};


//错误代码
class Solution1 {
public:
    int countPartitions(vector<int>& a, int k) {
        int n = a.size();
        vector<int> dp(k + 1);
        ll s = accumulate(a.begin(), a.end(), 0LL);
        dp[0] = 1;
        ll lo = 2 * k - s;
        if(lo > 0) return 0;
        for(int x : a){
            for(int j = k; j >= 0; j--){
                if(j - x < lo) continue;
                if(j - x > 0) dp[j] += dp[j - x];
                else dp[j] += dp[0];
            }
            cout << dp[k] << "\n";
        }
        return dp[k];
    }
};