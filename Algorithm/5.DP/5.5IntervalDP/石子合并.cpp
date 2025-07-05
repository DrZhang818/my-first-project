#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.acwing.com/problem/content/6026/
/*
    DP 
    题意:
        给定一个长度为N的数组表示有N堆石子, 每堆石子的石子数量为A[i]
        你可以进行以下操作:
        op: 选择两堆相邻的石子合并成一堆, 代价为两堆石子数量之和
        求将N堆石子合并成一堆所需的最小代价
    关键思考:
        本题是决策类问题, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为:前缀和、双指针、数据结构
        首先思考暴力方式: 合并N堆石子需要N-1次操作, 有N-1中操作方式
        那么暴力枚举的复杂度就是(N-1)*(N-2)*...*1 = O(N!), 无法接受
        本题不可用贪心来解决, 因为局部最优不能扩展到全局最优
*/
constexpr int inf = 1000000000;
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for(int len = 2; len <= n; len++) {
        for(int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            dp[i][j] = inf;
            for(int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + pre[j] - pre[i - 1]);
            }
        }
    }
    cout << dp[1][n] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
