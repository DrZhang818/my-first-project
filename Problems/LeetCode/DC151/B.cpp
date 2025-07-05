#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/find-the-number-of-copy-arrays/
/*
    思维 || DP
    题意:
        给定一个长度为N的数组A和一个N × 2的二维数组B, 定义一个数组a是合法的
        当且仅当a[i] - a[i - 1] = A[i] - A[i - 1], 且a[i]∈[B[i][0], B[i][1]]
        要求计算出合法数组的数量
        范围: N∈[2,1e5]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先分析第一个条件, 两个数组的差分数组相同, 意味着任意元素确定了, 整个数组就确定了
        那我们不妨就让a[1]确定
        显然, 合法数组数量 <--> 合法的a[1]数量
        我们可以考虑暴力枚举a[1]的值, 时间复杂为O(MX), 对于1e9的范围来说, 显然超时
        因此我们可以利用DP来维护考虑前i个数, a[1]可取的最小值和最大值
        做法本质上是在求区间交集
*/
class Solution {
public:
    int countArrays(vector<int>& a, vector<vector<int>>& b) {
        int n = a.size();
        vector<int> dif(n + 1);
        for(int i = 1; i < n; i++) {
            dif[i] = a[i] - a[i - 1];
        }
        int lo = b[0][0], hi = b[0][1];
        for(int i = 1; i < n; i++) {
            lo += dif[i];
            hi += dif[i];
            lo = max(lo, b[i][0]);
            hi = min(hi, b[i][1]);
        }
        return lo <= hi ? hi - lo + 1 : 0;
    }
};