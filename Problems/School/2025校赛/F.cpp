#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

/*
    DP || 组合数学
    题意:
        给定一棵N个节点的树, 定义图G的权值为f(G) = ∑∑dis(i,j), i∈[1,N],j∈[1,N]
        你需要进行恰好一次操作:
        op: 选择两个点i,j, 满足dis(i,j) = 2, 在图上添加一条边(i,j)
        请你求出操作后得到的G'的最小权值f(G')是多少
        范围: N∈[3,2e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对于决策类题目, 我们首先尝试将题目拆解为 局面 + 问题
        局面: N个节点的树
        问题: 添加一条边能得到的最小权值
        我们先来挖掘问题中蕴含的性质:
        (1)设连接的边为(u,v), 中间点为x, 我们考虑添加边(u,v)后带来的影响
            由于树上两点间路径唯一, 因此在添加(u,v)之前, u到达v必须经过u->x->v
            这意味着, 把x作为根时, u,v两棵子树的点(p,q)的最短路径为:
                p->u->x->v->q
            添加(u,v)后, 最短路径为:
                p->u->v->q
            设以u为根的子树有sz[u]个点, 以v为根的子树有sz[v]个点
            则添加(u,v)后, f(G') = f(G) - sz[u] * sz[v]
        考虑如何求出初始的f(G)
        最优解是通过贡献法来做, 当然也可以利用树形DP
        定义dp[u] := 以u为根的子树T的权值f(T)
        可以利用树上背包的思想, 把u的子树v不断合并到u中
        转移时需要辅助的dp数组sum
        sum[u] := 以u为根的子树中所有点到达u的dis之和
        转移方程为
        dp[u] = dp[u] + dp[v] + sz[u] * sum[v] + sz[v] * sum[u] + sz[u] * sz[v];
        sum[u] += sum[v] + sz[v];
*/
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<ll> sz(n + 1, 1), dp(n + 1), sum(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            dp[u] = dp[u] + dp[v] + sz[u] * sum[v] + sz[v] * sum[u] + sz[u] * sz[v];
            sum[u] += sum[v] + sz[v];
            sz[u] += sz[v];
        }
    };
    dfs(1, 0);
    ll tot = dp[1], mx = 0;
    auto dfs2 = [&](this auto &&self, int u, int fa) -> void {
        ll mx1 = 0, mx2 = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
            ll x = sz[v], y = n - sz[u];
            mx = max(mx, x * y);
            if(sz[v] > mx1) {
                mx2 = mx1;
                mx1 = sz[v];
            } else if(sz[v] > mx2) {
                mx2 = sz[v];
            }
        }
        mx = max(mx, mx1 * mx2);
    };
    dfs2(1, 0);
    cout << (tot - mx) * 2 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
