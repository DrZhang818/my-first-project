#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2107/problem/D
/*
    树的直径 || 搜索 || 贪心
    题意:
        给定一颗N个节点的树和一个空数组, 起初每个节点都有一个苹果, 你可以进行以下操作:
        op: 选择一条合法路径(u,v), 摘掉路径上的所有苹果
            一条路径是合法的, 当且仅当u->v的简单路径上每个节点都有苹果
            设d是路径上苹果的个数, 你将在数组尾部依次添加d,u,v三个数字
        请你通过操作最大化得到的数组的字典序, 输出这个数组
        范围: n∈[1,1.5e5], u,v∈[1,n]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        题目要求字典序最大, 因此我们考虑从左到右最大化数字
        要让d最大, 显然就是挑选直径
        要让u,v最大, 那么就是在所有最长的链中找端点编号最大的
        首先, 我们思考如何找到一棵树的最优(d,u,v)
        这可以用贪心法求树的直径来解决, 只要两次dfs, 并且每次dfs都最大化端点编号
        接着, 我们思考如何标记路径u->v被选过
        这可以用fa数组记录, fa[i]表示以u为根时, i的父节点
        这样第二次以u为根dfs找到v后, 从v不断向上跳就找到了路径(u,v)
        接下来就是递归解决剩下的所有子树, 我们着重分析下时间复杂度:
        由于树的特殊性质, 每次选出一条链后, 删除链上所有节点, 整棵树会被分割成若干个
        更小规模的树, 可以证明, 每次直径至少-2
        这意味着我们最多进行sqrt(n)次就能结束递归, 时间复杂度为O(n * sqrt(n))
        由于每次操作是删除一条链, 因此只有与链相邻的连通分量会受到影响, 这一点非常重要
        我们可以跳过对那些不受干扰的子树的计算, 从而保证每个连通分量只计算一次        
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
    vector<bool> vis(n + 1);
    vector<int> p(n + 1);
    int x = -1, y = -1, len = 0;
    auto dfs = [&](this auto &&self, int u, int fa, int dep) -> void {
        p[u] = fa;
        if(dep > len || dep == len && u > x) x = u, len = dep;
        for(int v : adj[u]) if(v != fa && !vis[v]) self(v, u, dep + 1);
    };
    vector<vector<int>> ans;
    auto work = [&](this auto &&self, int u) -> void {
        x = -1, y = -1, len = 0;
        dfs(u, -1, 1);
        len = 0, y = x;
        dfs(x, -1, 1);
        ans.push_back({len, max(x, y), min(x, y)});
        for(int i = x; i != -1; i = p[i]) {
            vis[i] = true;
        }
        for(int i = x; i != -1; i = p[i]) {
            for(int v : adj[i]) {
                if(!vis[v]) {
                    self(v);
                }
            }
        }
    };
    work(1);
    sort(ans.begin(), ans.end(), greater());
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << " \n"[i == ans.size() - 1];    
    }
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
