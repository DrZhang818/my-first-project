#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P3388
/*
    Tarjan || 图论 || 树形DP
    题意:
        给定N个点M条边的无向图, 求图的割点
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数据结构
        割点就是删除该点后使得连通块数量增加的点
        首先思考暴力做法, 对于每个点跑一次dfs, 时间复杂度为O(n*(n+m)), 需要优化
        我们可以利用Tarjan算法来求割点, 即利用"深搜优先生成树"求割点
        从任意节点出发进行dfs, 保证每个节点只进出一次, 这样就得到了图G的生成树T
        用dfn数组记录每个节点访问到的时间戳, 按时间戳给节点编号
        算法的核心是维护一个low数组, low[x]表示节点x沿着合法路径能访问到的最小时间戳
        一个路径是合法的, 当且仅当x的父节点不在路径内部出现
        如果我们发现节点u有个儿子节点v, 满足low[v] >= dfn[u], 说明v被u隔断了, u就成了割点
        low数组的状态转移可以利用树形DP来实现
        对于节点u, 记它的儿子节点为v, 非父邻居节点为w
        则low[u] = min ( min{low[v]}, dfn[w])
        这里判断是否是u的儿子节点可以根据dfn[v]是否为0来判断
        如果dfn[v]是0, 说明还没有访问过, 那么肯定就是u的儿子节点
        否则, 就是u的邻居节点
        特判: 如果u是根节点, 我们不能利用low[v] >= dfn[u]来判断
        因为不存在比dfn[u]更小的时间戳了, 此时这个条件恒成立
        但显然, 如果u只有一个儿子节点, 删除u之后连通分量不会增加
        因此这里特判方法就看u是否有两个以上的儿子节点
        
        注意本题的图不一定是连通图, 因此需要每个节点都跑一下Tarjan
        细节: 如果含有重边或自环, 算法仍然成立
*/
int n, m, id = 0, rt;
vector<vector<int>> adj;
vector<int> dfn, low;
set<int> st;
void dfs(int u, int fa) {
    dfn[u] = low[u] = ++id;
    int son = 0;
    for(int v : adj[u]) {
        if(!dfn[v]) {
            son++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(u != rt && low[v] >= dfn[u]) {
                st.insert(u);
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(u == rt && son >= 2) {
        st.insert(u);
    }
}
void solve() { 
    cin >> n >> m;
    adj.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            rt = i;
            dfs(i, 0);
        }
    }
    cout << st.size() << "\n";
    for(int x : st) {
        cout << x << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
