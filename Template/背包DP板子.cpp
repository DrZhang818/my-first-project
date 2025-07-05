#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/coin-change/
/*
    DP —— 完全背包
    完全背包板子题:
        该题类型为恰好型求最小, 注意完全背包是正序转移
    以下写了几个变形题目:
        1.恰好型求最小
        2.恰好型求最大
        3.恰好型求方案数
        4.至多型求最大
        5.至多型求方案数
        6.至少型求最小
        7.至少型求方案数(无穷解)
*/

int solve(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> memo(n + 1, vector<int>(amount + 1, -1));
    function<int(int, int)> dfs = [&](int i, int j) -> int{
        if(i == 0){
            return j == 0 ? 0 : INT_MAX / 2;
        }
        int& res = memo[i][j];
        if(res != -1){
            return res;
        }
        if(j < coins[i - 1]){
            return res = dfs(i - 1, j);
        }
        return res = min(dfs(i - 1, j), dfs(i, j - coins[i - 1]) + 1);
    };  
    int ans = dfs(n, amount);
    return ans < INT_MAX / 2 ? ans : -1;   
}
//优化成dp
int solve1(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, INT_MAX / 2);
    dp[0] = 0;
    for(int x : coins){
        for(int j = x; j <= amount; j++){
            dp[j] = min(dp[j], dp[j - x] + 1);
        }
    }
    return dp[amount] < INT_MAX / 2 ? dp[amount] : -1;
}
//恰好型求最大
int solve2(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, INT_MIN / 2);
    dp[0] = 0;
    for(int x : coins){
        for(int j = x; j <= amount; j++){
            dp[j] = max(dp[j], dp[j - x] + 1);
        }
    }
    return dp[amount] >= 0 ? dp[amount] : -1;
}
//恰好型求方案数
int solve3(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for(int x : coins){
        for(int j = x; j <= amount; j++){
            dp[j] = dp[j] + dp[j - x];
        }
    }
    return dp[amount];
}
//至多型求最大(也可以用amount / minElement计算)
int solve4(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, 0);
    for(int x : coins){
        for(int j = x; j <= amount; j++){
            dp[j] = max(dp[j], dp[j - x] + 1);
        }
    }
    return dp[amount];
}
//至多型求方案数
int sovle5(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, 1);
    for(int x : coins){
        for(int j = x; j <= amount; j++){
            dp[j] = dp[j] + dp[j - x];
        }
    }
    return dp[amount];
}
//至少型求最小(也可以用amount / maxElement计算)
int solve6(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, INT_MAX / 2);
    dp[0] = 0;
    for(int x : coins){
        for(int j = 0; j <= amount; j++){
            dp[j] = min(dp[j], dp[max(j - x, 0)] + 1);
        }
    }
    return dp[amount];
}
//至少型求方案数(不正确)
int solve7(vector<int>& coins, int amount){
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for(int x : coins){
        for(int j = 0; j <= amount; j++){
            dp[j] = dp[j] + dp[max(j - x, 0)];
        }
    }
    return dp[amount];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  

    int n, k;
    cin >> n;
    vector<int> coins(n);
    for(auto& c : coins) cin >> c;
    cin >> k;
    int ans = solve7(coins, k);
    cout << ans << "\n";
    return 0;
}