#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc411/tasks/abc411_f
/*
    启发式合并 || 并查集
    题意:
        给定一个N个节点M条边的无向图, 无自环和重边. 接下来有Q次询问, 每次询问如下:
        给定一个编号i, 将第i条边所连的两个点缩为一个点, 然后回答图中剩余边的总数
        注意: 缩点后如果出现自环则去掉, 出现重边则只保留一条边
        范围: N∈[2,3e5], M∈[1,3e5]
    关键思考:
        本题为数据结构类题目, 需要读清题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先观察题目性质, 设第i次查询将u,v两个点进行合并, 得到的新图为G'
        我们需要高效地统计G'和G的边数变化
        显然, |e(G')| < |e(G)|, |v(G')| = |v(G)| - 1 (当u,v是有效合并时)
        暴力的合并方式是: 开一个新点, 把u,v的邻居(不能是u,v本身)全部加入新点的邻居, 然后去重
        这样时间复杂度显然是O(n^2)的, 不可接受
        深入思考后我们发现, 可以钦定其中一个点为新点, 这样就可以节省掉一些时间开支
        假设钦定u为新的节点, 那么我们该如何将adj[v]合并到adj[u]呢?
        设adj[v]中的一个节点为o, 下面考虑u,v,o三者间的关系:
        (1)如果o = u:
            此时缩点后变为u->u, 由于题目不允许出现自环, 因此这条边应该被移除, 答案-1
            adj[u]保持不变, adj[o]移除节点v
        (2)如果o也在adj[u]中:
            此时缩点后有两条u->o的边, 由于题目不允许出现重边, 因此这条边应该被删除, 答案-1
            adj[u]保持不变, adj[o]移除节点v
        (3)如果o != u 且 o不在adj[u]中:
            此时缩点后多了u->o的边, 删除v->o的边, 答案不变
            adj[u]新增节点o, adj[o]移除节点v, adj[o]新增节点u
        以上并没有讨论adj[v]的改动情况, 因为当我们钦定u为新节点后, 得到的新图G'中将不存在节点v
        因此可以无需维护adj[v]
        特别注意: 如果真的需要维护adj[v], 一定不能边遍历边维护!!!
        由于涉及到增加/删除/去重操作, 显然用set维护最为合适(也可以uset, 但不推荐)
        然而这样的随意钦定u为新点是有问题的, 这样合并的效率为O(|adj[u]|)
        如果我们很不幸地每次合并时都有|adj[u]| > |adj[v]|, 最坏时间复杂度为O(n^2)
        这时可以用神秘的启发式合并, 每次钦定较小的作为新点, 即min(|adj[u]|, |adj[v]|)
        这样对于任何一个点最多进行logn次合并, 总时间复杂度是O(nlogn)
        如果用set维护, 时间复杂度是O(nlognlogn)
        最后, 如何维护新图的点集?
        可以用并查集来实现
*/
struct info {
    int u, v;
};
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void solve() {
    int n, m;
    cin >> n >> m;
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<set<int>> adj(n + 1);
    vector<info> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
        e[i].u = u, e[i].v = v;
    }  
    int q, tot = m;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        auto [u, v] = e[x];
        u = find(u), v = find(v);
        if(u != v) {
            if(adj[v].size() > adj[u].size()) swap(u, v);
            for(int o : adj[v]) {
                if(o == u || adj[u].count(o)) {
                    tot--;
                    adj[o].erase(v);
                } else {
                    adj[u].insert(o);
                    adj[o].erase(v);
                    adj[o].insert(u);
                }
            }
            fa[v] = u;
        }
        cout << tot << "\n";
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
