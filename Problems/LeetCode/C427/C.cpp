#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/maximum-subarray-sum-with-length-divisible-by-k/description/
/*
    前缀和(LC分1850)
    题意: 给定前缀和数组, 计算最大的s[j]-s[i], 满足i<j且j-i是k的倍数
    要使s[j]-s[i]尽量大, s[i]要尽量小
    观察发现对于固定的j, 可选的i要满足i == j - pk, 即i与j模k同余
    因此, 我们可以按照模k的余数分组维护最小值
*/
//优化做法1:
class Solution{
    ll maxSubarraySum(vector<int>& nums, int k){
        ll ans = LLONG_MIN;
        vector<ll> sum(n + 1), min_sum(k, LLONG_MAX / 2);//防止下面减法溢出
        for(int i = 0; i < n; i++) sum[i + 1] = sum[i] + nums[i];
        for(int i = 0; i <= n; i++){
            int j = i % k;
            ans = max(ans, sum[i] - min_sum[j]);
            min_sum[j] = min(min_sum[j], sum[i]);
        }
        return ans;
    }    
};
//优化做法2: 枚举右维护左
/*
    前缀和数组都是1-index, 如何边遍历边维护min_sum呢？
    即规定sum[-1] = 0, 那么min_sum在模k的意义下就是min_sum[k - 1] = 0
    即可省去前缀和数组所需空间
*/
class Solution{
    ll maxSubarraySum(vector<int>& nums, int k){
        ll ans = LLONG_MIN, sum = 0;
        vector<ll> min_sum(k, LLONG_MAX / 2);
        for(int i = 0; i < n; i++){
            int j = i % k;
            sum += nums[i];
            ans = max(ans, sum - min_sum[j]);
            min_sum[j] = min(min_sum[j], sum);
        }
        return ans;
    }
};
//比赛时做法 前缀和 + 动态规划
//本质是在维护最大值
class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<ll> dp(n + 1, 0);
        ll ans = LLONG_MIN;
        vector<ll> sum(n + 1);
        for(int i = 0; i < n; i++){
            sum[i + 1] = sum[i] + nums[i];
        }
        for(int i = 1; i <= n; i++){
            if(i < k){
                continue;
            }
            dp[i] = max(dp[i - k] + sum[i] - sum[i - k], sum[i] - sum[i - k]);
            ans = max(ans, dp[i]);
        }
        return ans == LLONG_MIN ? -1 : ans;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    return 0;
}