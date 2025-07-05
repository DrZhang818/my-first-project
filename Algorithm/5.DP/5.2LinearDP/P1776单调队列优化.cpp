#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P1776
/*
    DP || 单调队列优化
    题意:
        给定n种物品, 每种物品的属性为: 价值V, 重量W, 件数M
        现在你有一个最大承重为w的背包, 要求计算出能获得的最大价值
    关键思考:
        本题为决策类题目, 常用思考方式为暴力 -> DP || 贪心, 常用优化手段为前缀和、双指针...
        定义dp[i][j] := 考虑前i件物品, 背包承重为j时获得的最大价值
        朴素的想法是枚举第i件物品选了0,1,...,k个, k∈[0, min(M[i], j // W[i])]
        则有转移方程为: dp[i][j] = max(dp[i - 1][j - k * W[i]] + k * V[i])
        但这样的时间复杂度为O(nwk), 需要优化
        与完全背包不同的是, k∈[0, min(M[i], j // W[i])],这里有了个M[i]的限制导致我们无法利用dp[i][j-W[i]]
        本质上, 完全背包需要知道0 -> j范围内的最大值
               而多重背包需要知道max(0, j - W[i]*M[i]) -> j范围内的最大值
        外层循环i固定时, W[i] * M[i]固定, 因此就相当于要求一个定长滑窗的最大值, 这显然可以用单调队列完成
        但是, 我们要的不是范围内所有数的最大值:   
            当我们计算j时, 我们要知道上一层的j - k*W[i]最大值
            而这些数的共同特征是模W[i]同余的, 所以我们可以按照W[i]的余数进行分类
        分类后, 我们对每个类别分别做单调队列, 枚举到承重j时, 窗口内记录了之前最大值对应的载重T
        那么转移方程就是 dp[i][j] = dp[i-1][T] + (j - T) / W[i] * V[i]
*/
void solve(){ 
    int n, w;
    cin >> n >> w;
    vector<int> V(n + 1), W(n + 1), M(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> V[i] >> W[i] >> M[i];
    }
    vector<vector<int>> dp(2, vector<int>(w + 1));
    for(int i = 1; i <= n; i++) {
        auto &pre = dp[(i - 1) % 2], &cur = dp[i % 2];
        for(int rem = 0; rem < W[i]; rem++) {
            deque<int> q;
            for(int j = rem; j <= w; j += W[i]) {
                while(!q.empty() && pre[j] >= pre[q.back()] + (j - q.back()) / W[i] * V[i]) {
                    q.pop_back();
                }
                q.push_back(j);
                while(!q.empty() && q.front() < max(0, j - M[i] * W[i])) {
                    q.pop_front();
                }
                cur[j] = max(pre[j], pre[q.front()] + (j - q.front()) / W[i] * V[i]);
            }
        }
    }
    cout << dp[n % 2][w] << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
