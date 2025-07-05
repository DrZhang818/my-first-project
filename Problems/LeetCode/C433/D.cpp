#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/
/*
    单调栈 || 组合数学 || 贡献法
    题意:
        给定一个长度为n的数组和一个整数k, 要求计算出至多k个元素的所有子数组
        的最大元素和最小元素之和
    关键思考:
        本题是907题的一个hard版本, 难度在于如何计算"有多少个包含x的大小至多为k的子数组个数"
        首先观察出一个性质:
        (1)最大元素的贡献计算和最小元素的贡献计算可以分开独立计算, 并且逻辑基本一致
        那么就可以单独研究如何求出每个元素作为最小值出现时提供的贡献
        这时就需要使用单调栈扩展出左右边界(有效范围), 下面代码采取开区间写法
        扩展之后, 问题就转化为:
        求解 包含x的长度至多为k的子数组个数
        方法有两种:(1)直接计算 (2)容斥
        (1)直接计算, 借鉴DP思想, 只需要枚举右端点, 计算以j结尾的子数组个数
           即∑[j = i->min(r-1,i+k-1)] min(k-(j-i), i-l)
           =∑[j = 0->min(r-i-1,k-1)] min(k-j, i-l)
           这里可以采取分段求和来拆解min函数
           当k - j < i - l, 即j > k - i + l时, min函数固定为(k-j)
           当j <= k - i + l时, min函数固定为(i-l)
           因此可以令t = min(r-i-1, k-1)
           根据t与k-i-l的关系来划分
           特别注意, k-i-l可能小于0, 因此也要讨论这种情况
           具体实现见代码
        (2)利用容斥原理计算
            包含 x 的长度至多为 k 的子数组个数，等于：
                开区间 (L,R) 中的所有长度至多为 k 的子数组个数，
                减去开区间 (L,i) 中的长度至多为 k 的子数组个数，
                减去开区间 (i,R) 中的长度至多为 k 的子数组个数。
            问题转化为如何计算开区间 (L,R) 中的所有长度至多为k的子数组个数
            设开区间长度为m
            如果m <= k
                此时长度为1的有m个
                    长度为2的有m-1个
                    ...
                    长度为m的有1个
                总个数为m(m+1)/2
            如果m > k
                此时长度为1的有m个
                    长度为2的有m-1个
                    ...
                    长度为k的有m-k+1个
                总个数为(2m-k+1)k/2
*/
class Solution1 {
public:
    long long minMaxSubarraySum(vector<int>& a, int k) {
        int n = a.size();
        ll ans = 0;
        vector<int> left(n, -1), right(n, n);
        stack<int> stk;
        for(int i = 0; i < n; i++){
            while(!stk.empty() && a[stk.top()] >= a[i]){
                right[stk.top()] = i;
                stk.pop();
            }
            if(!stk.empty()) left[i] = stk.top();
            stk.push(i);
        }
        for(int i = 0; i < n; i++){
            int l = left[i], r = right[i];
            ll t = min(r - i - 1, k - 1);
            if(t <= k + l - i){
                ans += a[i] * (t + 1) * (i - l);
            }else if(k + l - i > 0){
                ans += a[i] * ((k + l - i + 1) * (i - l) + (i - l - 1 + k - t) * (t - k + i - l) / 2);
            }else{
                ans += a[i] * (2 * k - t) * (t + 1) / 2;
            }
        }
        while(!stk.empty()) stk.pop();
        for(int i = 0; i < n; i++){
            left[i] = -1;
            right[i] = n;
        }
        for(int i = 0; i < n; i++){
            while(!stk.empty() && a[stk.top()] <= a[i]){
                right[stk.top()] = i;
                stk.pop();
            }
            if(!stk.empty()) left[i] = stk.top();
            stk.push(i);
        }
        for(int i = 0; i < n; i++){
            int l = left[i], r = right[i];
            ll t = min(r - i - 1, k - 1);
            if(t <= k + l - i){
                ans += a[i] * (t + 1) * (i - l);
            }else if(k + l - i > 0){
                ans += a[i] * ((k + l - i + 1) * (i - l) + (i - l - 1 + k - t) * (t - k + i - l) / 2);
            }else{
                ans += a[i] * (2 * k - t) * (t + 1) / 2;
            }
        }
        return ans;
    }
};
class Solution {
public:
    long long minMaxSubarraySum(vector<int>& a, int k) {
        int n = a.size();
        ll ans = 0;
        vector<int> left(n, -1), right(n, n);
        stack<int> stk;
        auto count = [&](int m) -> ll{
            if(m <= k){
                return (ll)m * (m + 1) / 2;
            }
            return (ll)(2 * m - k + 1) * k / 2;
        };
        for(int i = 0; i < n; i++){
            while(!stk.empty() && a[stk.top()] >= a[i]){
                right[stk.top()] = i;
                stk.pop();
            }
            if(!stk.empty()) left[i] = stk.top();
            stk.push(i);
        }
        for(int i = 0; i < n; i++){
            int l = left[i], r = right[i];
            ans += a[i] * (count(r - l - 1) - count(i - l - 1) - count(r - i - 1));
        }
        while(!stk.empty()) stk.pop();
        for(int i = 0; i < n; i++){
            left[i] = -1;
            right[i] = n;
        }
        for(int i = 0; i < n; i++){
            while(!stk.empty() && a[stk.top()] <= a[i]){
                right[stk.top()] = i;
                stk.pop();
            }
            if(!stk.empty()) left[i] = stk.top();
            stk.push(i);
        }
        for(int i = 0; i < n; i++){
            int l = left[i], r = right[i];
            ans += a[i] * (count(r - l - 1) - count(i - l - 1) - count(r - i - 1));
        }
        return ans;
    }
};