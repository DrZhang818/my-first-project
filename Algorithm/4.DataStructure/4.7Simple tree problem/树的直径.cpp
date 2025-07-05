#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/U81904
/*
    DP || 树的直径
    题意:
        给定一棵n个节点的树, 有n-1条无向带权边, 定义树中两点的距离为连接两点的路径边权之和
        树中最远的两个节点之间的距离为树的直径, 要求计算出树的直径
        形式化的, 定义d(u,v) := ∑w[u -> i -> v]
        要求计算 max{d(u, v)}, u,v∈[1,n], u ≠ v
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 前缀和、双指针、数据结构
        本题的解决方法有两种: 贪心 or DP
        当含有负边权的时候, 只能使用DP
        暴力法很简单, 枚举u和v即可, 时间复杂度为O(n^2), 需要优化
        我们可以尝试思考贪心||DP来优化这个问题
        贪心的想法就是任取一个节点, 找到距离该节点的最远点u, 再从u出发找到最远点v
        那么u和v就是直径的两端
        这是因为我们可以利用u和v来把树"拉直", 这样显然任何节点的最远点必然是u和v中的一个
        而树形DP的想法就是要利用最优子结构来减少重复计算
        由于直径的所在的链一定是链上节点的最长链, 所以我们可以这样做:
        定义dp[u] := 以u为根的子树中, 包含节点u的最长链的长度
        那么就有ans = max{dp[u]}, u∈[1,n]
        为什么对? 想象一颗树上的任何一条简单路径, 它一定有个最高的节点hi
        此时如果这条链是最长链, 根据定义, dp[hi]的值就是这条链的长度
        这样问题就转化成如何求解dp[u]
        我们考虑辅助函数F(u) := 从u出发, 在u的子树中能获得的最大权值
        那么dp[u]的转移就要枚举子节点v的F(v)
            用d1记录max({F(v) + d(u,v)})
            用d2记录次大
        这里如果F(v2) + d(u,v2) < 0, 我们可以不选这条次长链, 相当于链的一个端点为u
            如果F(v1) < 0, 也可以不选, 相当于链的一个端点为v1
*/
constexpr int inf = 1000000000;
void solve() { 
    int n;
    cin >> n;
    vector<vector<PII>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int ans = -inf;
    auto dfs = [&](auto &&dfs, int u, int fa) -> int {
        int d1 = -inf, d2 = -inf;
        for(auto &[v, w] : adj[u]) {
            if(v == fa) continue;
            int temp = max(dfs(dfs, v, u), 0) + w;
            if(temp >= d1) {
                d2 = d1;
                d1 = temp;
            } else if(temp > d2) {
                d2 = temp;
            }
        }
        d2 = max(d2, 0);
        ans = max(ans, d1 + d2);
        return d1 == -inf ? 0 : d1;
    };
    dfs(dfs, 0, -1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
