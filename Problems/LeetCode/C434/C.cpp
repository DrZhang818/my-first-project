#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/maximum-frequency-after-subarray-operation/description/
/*
    合法子序列 DP || 状态机 DP || 贪心Kanade算法(增益数组)
    本题最优解为合法子序列DP + 懒更新, 下面只写这种方法的思路
    题意:
        给定一个长度为n的数组和一个整数k, 你可以进行至多一次以下操作
        op: 选择一个子数组a[i:j], 并选择一个整数x, 然后让数组所有元素增加x
        问经过操作后, 原数组中k出现的最大频率
    关键思考:
        状态表示:
            集合:a[:i]中选择以a[i]结尾子数组的集合
            属性:max
            定义dp[x] := 以x结尾所能获得的最大值
            额外定义ans记录全局最大值, 这样就可以
        状态转移:
            当x == k的时候, 直接更新全局最大值ans += 1即可
            当x != k的时候, 更新dp[x]
                逻辑如下:
                    以x结尾的子数组, 即右端点固定为x, 此时就要最大化1~i-1的频率
                    也就是要最优化左端点l
                    此时dp[x]记录的就是上一次出现x时的最优答案
                    假设以下情景: ***x***x
                    最优左端点l要么是继承上一次x的左端点, 要么就是l == r
                    这是因为如果左端点夹在上一次和这一次之间的话
                    中间不会再次出现x, 那么答案与l == r相比一定是不优的
                    因此这里可以利用贪心思想实现高效转移
            在更新的时候只需要更新dp[x]和全局最大值ans
            这是因为我们对于任意的a[i], 我们的ans记录的一定是a[i]最后一次出现的最大值
            这样对于每一个a[i]的最大值都记录了下来, 就实现了全局覆盖
            在保证答案不漏的前提下, 就能保证答案ans是全局最优
*/
class Solution {
public:
    int maxFrequency(vector<int>& a, int k) {
        int n = a.size();
        vector<int> dp(51);
        int ans = 0, curk = 0;
        for(auto c : a){
            if(c == k){
                ans++;
                curk++;
            }else{
                dp[c] = max(dp[c], curk) + 1;
                ans = max(ans, dp[c]);
            }
        }
        return ans;
    }
};

constexpr int inf = 1000000000;
class Solution1 {
public:
    int maxFrequency(vector<int>& nums, int k) {
        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;
        for (auto c : st) {
            vector<int> dp(3, -inf);
            dp[0] = 0;
            for (auto x : nums) {
                dp[2] = max(dp[2], dp[1]) + (x == k);
                dp[1] = max(dp[1], dp[0]) + (x == c);
                dp[0] += (x == k);
            }
            ans = max({ans, dp[1], dp[2]});
        }
        return ans;
    }
};