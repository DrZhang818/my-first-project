#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/sum-of-subarray-minimums/description/
/*
    单调栈 || 贡献法
    题意:
        给定一个长度为n的数组, 要求计算出每个子数组的最小值之和
        答案对1e9 + 7取模
    关键思考:
        直接暴力计算每个子数组的最小值显然时间复杂度过高O(n^3)
        那么可以思考每个元素是哪些子数组的最小值, 求出它在构成答案时的贡献次数
        这样问题就变成求每个元素向左右扩展的最远距离
        具体来说, 需要找到每个元素左边最近的比它小的值和右边最近的比它小的值
        但这样会出现hack数据
        如[1,2,3,2,1]
        这样第一个2的范围是(0,5), 第二个2的范围还是(0,5) 就会出现重复计数
        这样就需要通过特殊约定来去重
        一种方法是规定右边界找最近的<= x的数
        这样第一个2范围就是(0,3) 第二个是(0,5)避免了重复计数
        单调栈可以很方便地解决这一问题
        最后的计算公式就是∑a[i] * (i - l[i]) * (r[i] - i)
*/
const int MOD = 1000000007;
//优化解法
class Solution1 {
public:
    int sumSubarrayMins(vector<int>& a) {
        ll ans = 0;
        int n = a.size();
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
            ans += (ll)a[i] * (i - left[i]) * (right[i] - i) % MOD; 
            ans %= MOD;
        }
        return ans;
    }   
};
//三次遍历
class Solution {
public:
    int sumSubarrayMins(vector<int>& a) {
        ll ans = 0;
        int n = a.size();
        vector<int> left(n, -1), right(n, -1);
        stack<int> stk;
        for(int i = 0; i < n; i++){
            while(!stk.empty() && a[stk.top()] >= a[i]){
                stk.pop();
            }
            if(!stk.empty()) left[i] = stk.top();
            stk.push(i);
        }
        while(!stk.empty()) stk.pop();
        for(int i = n - 1; i >= 0; i--){
            while(!stk.empty() && a[stk.top()] > a[i]){
                stk.pop();
            }
            if(!stk.empty()) right[i] = stk.top();
            stk.push(i);
        }
        for(int i = 0; i < n; i++){
            ans = ans + a[i] * (i - left[i]) * (right[i] - i) % MOD; 
            ans %= MOD;
        }
        return ans;
    }   
};
