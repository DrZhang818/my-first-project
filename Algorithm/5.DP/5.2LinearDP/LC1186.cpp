#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
//https://leetcode.cn/problems/maximum-subarray-sum-with-one-deletion/description/
/*
    DP
    题意:
        给定一个长度为N的数组, 你需要从中选择一个非空子数组, 并至多从这个子数组中删除一个元素,
        执行删除操作后子数组必须仍然非空, 该子数组剩余元素的总和为你的得分
        请求出你能得到的最大得分
        范围: N∈[1,1e5], a[i]∈[-1e4, 1e4]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对于子数组问题, 我们经典的做法是: 枚举以a[i]为结尾的子数组
        定义dp[i][j] := 考虑前i个元素, 以a[i]为结尾的子数组, 至多删除j个元素得到的最大得分
        若删除a[i], 则转移方程为:
            dp[i][1] = dp[i - 1][0]
        若不删a[i], 则转移方程为:
            dp[i][1] = max(dp[i - 1][1], 0) + a[i]
            dp[i][0] = max(dp[i - 1][0], 0) + a[i]
        答案为全局max{dp[1]}
*/
class Solution {
public:
    int maximumSum(vector<int>& a) {
        int n = a.size(), ans = a[0];
        array<int,2> dp;
        dp[0] = dp[1] = a[0];
        for(int i = 1; i < n; i++) {
            dp[1] = max(max(0, dp[1]) + a[i], dp[0]);
            dp[0] = max(0, dp[0]) + a[i];
            ans = max(ans, dp[1]);
        }
        return ans;
    }
};