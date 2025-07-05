#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/form-largest-integer-with-digits-that-add-up-to-target/description/
/*
    DP || 字典序贪心
    题意:
        给定一个长度为n的数组A和一个整数k, 你可以进行以下操作:
        op: 给当前结果添加一个数位(i + 1), 消耗成本为A[i]
        要求总成本恰好等于k, 且添加的数位中没有0, 在此条件下最大化结果
        答案以字符串形式返回
        如果无法得到任何整数, 返回"0"
        范围: A[i]∈[1,5000], k∈[1,5000]

*/
constexpr int inf = 1000000000;
class Solution {
public:
    string largestNumber(vector<int>& a, int k) {
        vector<int> dp(k + 1, -inf); 
        int n = a.size();
        dp[0] = 0;
        for(int i = 0; i < n; i++) {
            int x = a[i];
            for(int j = x; j <= k; j++) {
                dp[j] = max(dp[j], dp[j - x] + 1);
            }
        }
        if(dp[k] < 0) return "0";
        string ans = "";
        for(int i = n - 1, j = k; i >= 0; i--) {
            for(int x = a[i]; j >= x && dp[j] == dp[j - x] + 1; j -= x) {
                ans += '1' + i;
            }
        }
        return ans;
    }
};