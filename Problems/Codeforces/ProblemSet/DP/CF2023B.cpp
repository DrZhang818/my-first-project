#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://codeforces.com/problemset/problem/2023/B
/*
    DP || 最短路 || 贪心
    题意:
        给定N道题目, 第i道题目得分为a[i], 属性为b[i]
        起初, 你在决策第一道题目. 对于第i道题目, 你有两种选择:
        (1)提交该题目并获得该题得分, 接下来你可以查看j < i的题目
        (2)跳过该题目, 接下来你可以查看j <= b[i]的题目
        在可查看范围内, 你必须选择编号最大的一个未被决策过的题目
        如果在可查看范围内, 所有题目均被决策过, 则比赛结束, 不再继续作答
        请你最大化你的最终得分
        范围: N∈[1,4e5], a[i]∈[1,1e9], b[i]∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 我们发现本题的决策目标其实是用op1配合op2到达一个合适的位置
        然后用op1收集该位置之前的所有未被决策的位置的得分
        我们考虑枚举被收集题目的最大编号i, 满足所有被收集的题目编号j <= i
        我们可以断定, 最优解情况下的i, 一定是由j < i的题目通过(2)到达
        否则, 假设i是从j > i的题目通过(2)到达
        那么直接从j不断使用(1)得到的分数 一定大于 从i不断使用(1)得到的分数
        这就划分了明确的阶段, 我们在考虑i时, 无需考虑在i+1~n跳过了多少分数
        这就极大简化了问题
        我们定义dp[i] := 决策题目i至少要跳过的得分
        对于最优的i, dp[i]记录的题目一定在1~i-1之间
        那么我们求出sum[1:i], 减掉dp[i], 就是答案
        但我们并不知道哪个i是最优的, 因此只需要每个都求一下并取最大值即可
        那么如何求解dp[i]呢?
        我们考虑dijkstra
        通过(1), 我们可以从i转移到i-1, 代价为0
        通过(2), 我们可以从i转移到b[i], 代价为a[i]
        为什么不用考虑i-1或b[i]已被决策的情况?
        假设v已被决策, 那么dp[v]一定先于dp[u]得到了更新, 因此dp[v] <= dp[u]
        因此, 用dp[v]去更新1~v-1一定比dp[u]更新1~v-1更优
        这就说明, 我们无需再考虑顺位情况, 如果编号最大的已被决策, 那么不进行更新
*/
struct info {
    int u;
    ll w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<ll> dp(n + 1, inf);
    priority_queue<info> q;
    q.emplace(1, 0);
    while(!q.empty()) {
        auto [u, w] = q.top(); q.pop();
        if(dp[u] != inf) continue;
        dp[u] = w;
        if(dp[b[u]] == inf) q.emplace(b[u], w + a[u]);
        if(dp[u - 1] == inf) q.emplace(u - 1, w);
    }
    ll ans = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        ans = max(ans, sum - dp[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
