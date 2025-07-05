#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/maximum-amount-of-money-robot-can-earn/
/*
    网格图DP || DFS
    题意:
        给定一个二维矩阵, 每个点有一个权值, 你的任务是从左上角走到右下角(只能向右或向下), 并收集权值,
        同时你可以进行最多2次op操作, 要求最大化权值和
        op: 跳过当前权值计算
    关键思考:
        状态定义: dp[i][j][k] := 到达(i,j)点进行最多k次操作获得的最大权值
        let x = grid[i][j]
        初始状态:
                dp[1][1][0] = x
                dp[1][1][1] = dp[1][1][2] = max(x, 0)
        状态转移:
                if k > 0
                    dp[i][j][k] = max(dp[i-1][j][k] + x, dp[i][j-1][k] + x
                                      dp[i-1][j][k-1],   dp[i][j-1][k-1])
                else
                    dp[i][j][k] = max(dp[i-1][j][k] + x, dp[i][j-1][k] + x)
        最终答案即dp[n][m][2]
        优化:
            可以发现dp[i][j][k]在仅仅依赖于上一行和前一列
            这样就可以把第一个维度优化掉
            注意j要正序枚举, k要倒序枚举   思考方法: 看看当前状态的更新是否依赖于"更新后"的前一个状态
*/      
class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int n = coins.size(), m = coins[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(3,INT_MIN / 2));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int x = coins[i][j];
                if(i == 0 && j == 0){
                    dp[1][0] = x;
                    dp[1][1] = dp[1][2] = max(x, 0);
                    continue;
                }
                for(int k = 2; k >= 0; k--){
                    if(k == 0){
                        dp[j + 1][k] = max(dp[j][k], dp[j + 1][k]) + x;
                    }else{
                        dp[j + 1][k] = max({dp[j][k] + x, dp[j + 1][k] + x,
                                            dp[j][k - 1], dp[j + 1][k - 1]});
                    }
                }
            }
        }
        return dp[m][2];
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}