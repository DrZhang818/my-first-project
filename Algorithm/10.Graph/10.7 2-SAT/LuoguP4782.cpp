#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P4782
//推荐阅读: https://www.luogu.com.cn/article/5tnmwo5l
/*
    构造 || 2-SAT || SCC
    题意:
        给定N个布尔变量和M个约束条件, 每个约束条件由i,a,j,b构成, 表示x_i = a || x_j = b
        输出N个布尔变量的一组解, 无解输出"IMPOSSIBLE"
        范围 M∈[1,1e6], a,b∈{0,1}
    关键思考:: N∈[1,1e6],
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于或运算性质不强, 我们将其转化为蕴含关系
        x_i != a -> x_i = b && x_j != b -> x_i = a
        我们发现, 此时就变成了一个强约束问题, 箭头前面的成立后面的就必须成立
        因此我们就可以把问题转化成有向图上的问题
        我们把每个元素拆为两个点, 一共得到2N个点, 前N个表示x_i = 0, 后N个表示x_{i-N} = 1
        有向边表示若起点成立, 则终点一定成立
        下面我们只需要思考单独每个元素是否有解就可以了, 如果所有元素都有解, 那么就构造完成了
        如果一个元素拆出的两个点u,v, 存在有向图上的路径u->v, 则u非法, v合法
        (1)我们从简单情况开始考虑, 假设建图后得到的是一个DAG
        那么对DAG求拓扑序后, 合法点的拓扑序一定比非法点大, 每个元素按照拓扑序进行构造即可
        (2)如果建出来的图有环, 我们就无法利用拓扑序构造了, 并且有一个很严重的问题:
            可能既有u->v的路径, 又有v->u的路径, 这样这个元素就是无解的了, 整个问题也就无解了
            我们发现, 对有向图进行SCC缩点后正好可以解决这两个问题
            <1>如果u,v在同一个连通分量里面, 那么就可以判定为无解
            <2>如果不在一个连通分量里面, 那么我们需要进行分类讨论:
                1.如果SCC[u]与SCC[v]无边, 那么两个互不干扰, 怎么取都是合法的
                2.如果SCC[u]->SCC[v], 那么与上面做法一样, 我们应该让v合法
            Tarjan算法求解SCC时, 会自动地给SCC进行编号, 由于Tarjan是自底向上构建, 这保证了
            如果SCC[u]->SCC[v]的时候, SCC[v]的编号一定小于SCC[u]
            因此按照Tarjan算法算出来的实际上是缩点图的反拓扑序
        综上, 求解2-SAT问题就转化为求解SCC缩点图的拓扑序问题
        特别注意: 2-SAT问题存边必须成对存储, 否则在求解SCC序时会出错!
        例如A成立->B成立, 此时我们要存A->B和!B->!A 
*/
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(2 * n + 1);
    for(int i = 1; i <= m; i++) {
        int u, x, v, y;
        cin >> u >> x >> v >> y;
        adj[u + !x * n].push_back(v + y * n);
        adj[v + !y * n].push_back(u + x * n);
    }
    int timer = 0, cnt = 0;
    n *= 2;
    vector<int> low(n + 1), dfn(n + 1), scc(n + 1);
    stack<int> stk; 
    auto dfs = [&](auto &&dfs, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                dfs(dfs, v);
                low[u] = min(low[u], low[v]);
            } else if(!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            cnt++;
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                if(v == u) break;
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    }
    n /= 2;
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        if(scc[i] == scc[i + n]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        ans[i] = scc[i] > scc[i + n] ? 1 : 0;
    }
    cout << "POSSIBLE\n";
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
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
