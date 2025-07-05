#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P3225
/*
    构造 || vDCC缩点 || 组合数学
    题意:
        给定一个N个点M条边的无向连通图, 定义一个顶点集是合法的, 当且仅当对于任意i∈[1,N], 
        任意j∈[1,N]\{i}都可以不经过点i到达顶点集中的某个点
        求出合法顶点集的最小势size, 并求出有多少种不同的大小为size的合法顶点集
        范围: M∈[1,500], 保证答案小于2^64
    关键思考:
        本题为决策+计数类题目, 常用思考方式为: 暴力->DP||贪心+组合数学
        首先观察题目性质, 题目问的是无向图中删除某点后的连通性问题, 自然想到vDCC缩点图
        题目保证输入的是连通图, 那么vDCC缩点后得到的一定是一棵树, 每条边连接着割点和点双
        为了便于区分, 我们画图时候可以用圆圈代表割点, 三角代表点双
        我们从最特殊的情况开始考虑:
        (1)假设原图是点双连通图, 那么缩点后只有一个三角
            显然任意钦定两个点组成的顶点集都是合法的, 因此最小势为2, 方案数为C[n][2]
        (2)当原图存在割点时, 缩点后必然得到一个奇数层为圆圈, 偶数层为三角的树
            并且这棵树必然有偶数层
            观察这棵树, 我们发现每个叶子节点都是三角, 当我们把连接他的圆圈去掉时, 该节点
            就变为了孤立点, 而由于点双的特性, 内部仍然是连通的, 因此我们此时至少要选择其中
            一个顶点放入顶点集
            上面考虑了去掉圆圈后的情况, 并钦定选择内部的一个顶点k放入顶点集
            那么如果保留圆圈, 去掉k, 此时我们是不是要再选一个新的顶点呢?
            这是不需要的, 因为内部的其余顶点必然可以通过圆圈到达另一个叶子节点, 因为一个圆圈
            至少连接着两个三角, 假设另一个三角是叶子节点, 那么已经成立了, 假设另一个不是叶子节点,
            那么它的度数 >= 2, 因此必然还连接着另一个圆圈, ...
            因此, 我们证明了内部其余点可以沿着圆圈到达另一个叶子, 而叶子必有一个顶点在顶点集
        (3)上面对叶子节点进行了讨论, 我们发现每个叶子节点必须选出一个
            那么对于非叶子三角, 它有至少两个圆圈与之相连, 意味着可以到达至少两个不同的叶子,
            而我们每次只能去掉其中一个圆圈, 因此其内部的点必然会沿着没被去掉的圆圈走到叶子,
            从而到达这片叶子选定的顶点
            因此这种情况下不需要选新的顶点
        综上讨论, 除开第一种特判之外, 答案1就是缩点图中的叶子数量
        答案2就是(叶子大小 - 1)的累乘, 这里减1是因为不可选择叶子中的割点(圆圈)             
*/
int n;
void solve() {
    vector<int> id(502);
    int idx = 0;
    vector<vector<int>> adj(502);
    for(int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        if(!id[u]) id[u] = ++idx;
        if(!id[v]) id[v] = ++idx;
        adj[id[u]].push_back(id[v]);
        adj[id[v]].push_back(id[u]);
    }
    n = idx;
    vector<int> dfn(n + 1), low(n + 1), cut(n + 1);
    vector<vector<int>> dcc(n + 1);
    int timer = 0, cnt = 0, rt = 1;
    stack<int> stk;
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        int son = 0;
        for(int v : adj[u]) {
            if(!dfn[v]) {
                self(self, v, u);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    son++;
                    if(u != rt || son >= 2) {
                        cut[u] = 1;
                    }
                    ++cnt;
                    while(1) {
                        int x = stk.top(); stk.pop();
                        dcc[cnt].push_back(x);
                        if(x == v) break;
                    }
                    dcc[cnt].push_back(u);
                } 
            } else if(v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    dfs(dfs, 1, 0);
    if(cnt == 1) {
        cout << 2 << " " << n * (n - 1) / 2 << "\n";
        return;
    }
    vector<int> deg(cnt + 1);
    for(int i = 1; i <= cnt; i++) {
        for(int x : dcc[i]) {
            if(cut[x]) {
                deg[i]++;
            }
        }
    }
    ll ans1 = 0, ans2 = 1;
    for(int i = 1; i <= cnt; i++) {
        if(deg[i] == 1) {
            ans1++;
            ans2 *= dcc[i].size() - 1;
        }
    }
    cout << ans1 << " " << ans2 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 0;
    while(cin >> n) {
        if(n == 0) break;
        t++;
        cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
