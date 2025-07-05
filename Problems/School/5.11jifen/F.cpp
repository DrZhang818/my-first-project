#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc148/tasks/abc148_f
/*
    博弈论 || 最短路 || 思维
    题意:
        给定一颗N个节点的树, Alice位于x节点, Bob位于y节点, 每轮回合依次发生:
        (1)如果Alice和Bob位于同一节点, 游戏结束, 否则Alice移动到任意相邻一格的节点上
        (2)如果Alice和Bob位于同一节点, 游戏结束, 否则Bob移动到任意相邻一格的节点上
        Alice希望她走的步数尽可能多, Bob希望他走的步数尽可能少, 两人都按最优决策进行
        问最终Bob走多少步
        范围: N∈[2,1e5], x,y∈[1,N], x != y
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法: 枚举Alice的所有路线, 求解Bob最少走几步可以结束游戏, 更新答案 
        由于Alice的路线方案非常多, 显然会超时
        对于这种状态量爆炸的决策问题, 我们有两种常用解决方案:
        (1)利用等价关系划分状态, 排除等效冗余
        (2)贪心剪枝, 避免访问一定不优的状态
        通过观察题目性质, 我们发现可以用"路线终点"来划分不同的状态
        因为只要路线终点一样, 得到的答案一定是一样的
        
*/
void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<vector<int>> adj(n + 1);
    vector<int> disx(n + 1), disy(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    auto dfs = [&](this auto &&self, vector<int> &dis, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            dis[v] = dis[u] + 1;
            self(dis, v, u);
        }
    };
    dfs(disy, y, 0);
    dfs(disx, x, 0);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(disx[i] < disy[i]) {
            ans = max(ans, disy[i] - 1);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
