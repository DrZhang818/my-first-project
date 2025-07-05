#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

//https://leetcode.cn/problems/minimum-cost-to-divide-array-into-subarrays/description/
/*
    DP || 前缀和
    题意:
        给定两个长度为n的数组a和b, 和一个整数k
        你可以把a分割成多个子数组, 第i个子数组由元素a[l:r]组成
        其权值定义为: (∑a[:r] + k*i) * ∑b[l:r]
        i表示子数组的顺序, 第一个为1, 第二个为2, ...
        求出通过任何有效划分得到的最小权值
        n∈[1,1000], ai,bi∈[1,1000], k∈[1,1000]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法, 枚举每个位置分或不分, 并逐一计算, 时间复杂度为O(n * 2^n)
        对于这种划分型问题, 我们自然想到使用DP来优化这个过程
        但很麻烦的是, 权值计算中的次数i非常难处理, 于是尝试能否利用数学推导来简化权值计算
        首先对于子数组和问题, 最直接的手段是前缀和优化
        定义S为a的前缀和, T为b的前缀和
        式子转化为: S[r]*(T[r]-T[l-1]) + k*i*(T[r]-T[l-1])
        为了看清结构, 我们利用图形来辅助理解
        [                ]
        [   ][      ][   ]
             [      ][   ]
                     [   ]
         ×1     ×2     ×3
        假设数组被划分为三段, 子段和分别为A,B,C, 思考下i*(T[r]-T[l-1])的结果是什么
        我们惊讶的发现, 和是A + 2B + 3C
        稍作变形, 就变成(A + B + C) + (B + C) + C
        这不就是后缀和, ∑(T[n]-T[l-1])的结果吗
        因此∑i*(T[r]-T[l-1]) 就等于 ∑(T[n]-T[l-1])
        于是权值的计算就转化为: ∑(S[r]*(T[r]-T[l-1]) + k*(T[n]-T[l-1]))
        求解最小权值, 我们可以利用动态规划来解决
        (1) 定义dp[i] := 前i个数经过最优划分得到的最小权值和
        (2) 接下来思考状态转移方程
            枚举最后一个不同点, 考虑新加入的数被划分到哪一组, 等价于枚举区间左端点
            设当前右端点为i, 左端点j可以是[1,i], 由于涉及前缀和, 我们转化成枚举[0,i-1]
            即枚举的是左开右闭区间(j,i]
            因此dp[i] = min{dp[j] + S[i]*(T[i]-T[j]) + k*(T[n]-T[j])}
            注意: 这里的dp[i]并不是题目中的最小权值和, 而是我们转化后新定义的权值计算方式中
                  的最小值, 当所有数全部计算完之后, 二者才真正相等, 即dp[n]一定是正确的
        (3) 思考初始状态
            由于第i个状态的计算依赖于0~i-1的状态, 并且要取min, 因此可以设定为
            dp[0] = 0, dp[1:n] = inf
        (4) 答案就是dp[n]
*/
constexpr ll inf = 1e18;
class Solution {
public:
    ll minimumCost(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();
        vector<ll> prea(n + 1), preb(n + 1);
        for(int i = 1; i <= n; i++) {
            prea[i] = prea[i - 1] + a[i - 1];
            preb[i] = preb[i - 1] + b[i - 1];
        }
        vector<ll> dp(n + 1, inf);
        dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < i; j++) {
                dp[i] = min(dp[i], dp[j] + prea[i] * (preb[i] - preb[j]) + k * (preb[n] - preb[j]));
            }
        }
        return dp[n];
    }
};