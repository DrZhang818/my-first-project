#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


/*
    DP || 树的重心
    题意:
        给定一颗n个节点的树, 定义节点u为树的重心, 当且仅当删除节点u后得到的所有
        互不连通的子树中, 最大子树的节点数最少
        形式化的, 定义F(u) := 删除u后的最大子树节点数
        则我们要求 min{F(u)}
    关键思考:
        本题是决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 前缀和、双指针、数据结构
        暴力的做法很简单, 我们可以对每个节点u跑一遍dfs, 求解出它的F(u)
        这样的时间复杂度是O(n^2), 需要优化
        优化的关键在于如何减少重复计算
        我们发现, F(u)可以由u的所有儿子节点v转移得到
        (注: 这里的儿子节点是指u的邻居v中, 不等于fa的节点, 即人为规定的u的根)
        我们定义siz(u) := 以u为根的子树的节点个数
        那么siz函数就可以辅助计算F函数, 具体来说
        siz的转移方程为: siz(u) = 1 + Σsiz(v)
        F  的转移方程为: F(u) = max{ max{siz(v)} , n - siz(u) }
        这里利用了节点总数固定为n的优良性质, 通过容斥推导出fa的不含子树u的节点总数
        这样就通过自下而上的动态规划, 完成了重心的计算
    其他笔记:
        树的重心是树的基本问题之一, 其有以下5个性质
        (1)树的重心如果不唯一, 则至多有两个, 且这两个重心相邻。
        (2)以树的重心为根时, 所有子树的大小都不超过整棵树大小的一半。
        (3)树中所有点到某个点的距离和中, 到重心的距离和是最小的;如果有两个重心，那么到它们的距离和一样。
        (4)把两棵树通过一条边相连得到一棵新的树, 那么新的树的重心在连接原来两棵树的重心的路径上。
        (5)在一棵树上添加或删除一个叶子, 那么它的重心最多只移动一条边的距离。
        其中(2)是很常用的树的重心的判定定理, 我们可以利用这个性质实现判定重心
        具体方法见下文方法2, 利用 max{ max{siz(v)} , n - siz(u) } <= n // 2即可直接判断是否为重心

        如果我们要计算有向树中以任意节点u为根的子树的重心, u∈[1,n], 也是有O(n)的做法的
        具体见CF685B, 是性质(2)(4)的应用
*/


/*
    方法1:
    重心u满足: 删除u之后各连通分量的最大值最小
    所以我们可以定义F(u) := 以u为根的子树中节点最多的树的节点数
    那么答案就是max{F[u]}
*/
void solve(vector<vector<int>> &adj, int n){ 
    // int n;
    // cin >> n;
    // vector<vector<int>> adj(n);
    // for(int i = 0; i < n - 1; i++) {
    //     int u, v;
    //     cin >> u >> v;
    //     u--, v--;
    //     adj[u].push_back(v);
    //     adj[v].push_back(u);
    // }
    vector<int> dp(n);
    function<int(int,int)> dfs = [&](int u, int fa) -> int {
        int d = 1;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int t = dfs(v, u);
            d += t;
            dp[u] = max(dp[u], t);
        }
        dp[u] = max(dp[u], n - d);
        return d;
    };
    dfs(0, -1);
    int mn = *min_element(dp.begin(), dp.end());
    for(int i = 0; i < n; i++) {
        if(dp[i] == mn) {
            cout << i + 1 << "\n";
        }
    }
}

/*
    方法2:
    利用重心的判定定理
    如果一个节点u的F(u) <= n//2
    那么u就是整棵树的重心
    用siz[u]记录每个节点u的子树大小总和, 对应方法一的d
    weight[u]记录节点数最多的子树节点数
    max(weight[u], n - siz[u])对应方法一的dp[u]
*/
void solve2(vector<vector<int>> &adj, int n) {
    // int n;
    // cin >> n;
    // vector<vector<int>> adj(n);
    // for(int i = 0; i < n - 1; i++) {
    //     int u, v;
    //     cin >> u >> v;
    //     u--, v--;
    //     adj[u].push_back(v);
    //     adj[v].push_back(u);
    // }
    vector<int> siz(n, 1), weight(n, 0);
    vector<int> ans;
    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            dfs(dfs, v, u);
            siz[u] += siz[v];
            weight[u] = max(weight[u], siz[v]);
        }
        if(max(weight[u], n - siz[u]) <= n / 2) {
            ans.push_back(u);
        }
    };
    dfs(dfs, 0, -1);
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << "\n";
    }
}
//方法3, 对法2的空间优化
void solve3(vector<vector<int>> &adj, int n) {
    vector<int> ans;
    auto dfs = [&](auto &&dfs, int u, int fa) -> int {
        int siz = 1, weight = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            int t = dfs(dfs, v, u);
            siz += t;
            weight = max(weight, t);
        }
        if(max(weight, n - siz) <= n / 2) {
            ans.push_back(u);
        }
        return siz;
    };
    dfs(dfs, 0, -1);
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve2(adj, n);
    cout << "\n";
    solve3(adj, n);
    return 0;
}
    
