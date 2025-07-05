#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2812
/*
    SCC缩点
    题意:
        给定一张N个点M条边的有向图, 求SCC缩点后的入度为0的点的个数,
        以及至少需要连接几条边使得图满足强连通性
        范围: n∈[1,10000], m∈[1,50000]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、双指针、前缀和、数据结构
        问题一很简单, 缩点后统计即可
        下面讨论问题二:
        (1)如果图已经是强连通的, 那么答案自然是0
        (2)如果图不是强连通的, 我们考虑缩点图G
            假设G有a个入度为0的点, b个出度为0的点, 定义这些点为"特殊点"
            由于强连通图中每个点的出度和入度都不为0, 因此这些"特殊点"必须要添加边
            考虑通过环把G转化为强连通图, 那么所有出度为0的点就要连向入度为0的点
            显然我们可以通过max(a,b)条边将这些特殊点串起来, 得到一个强连通图
*/
int n, timer = 0, cnt = 0;
vector<vector<int>> adj;
vector<int> dfn, low, scc;
vector<bool> instk;
stack<int> stk;
void init() {
    adj.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
    scc.resize(n + 1);
    instk.resize(n + 1);
}
void dfs(int u, int fa) {
    dfn[u] = low[u] = ++timer;
    instk[u] = true;
    stk.push(u);
    for(int v : adj[u]) {
        if(!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        ++cnt;
        while(1) {
            int v = stk.top(); stk.pop();
            instk[v] = false;
            scc[v] = cnt;
            if(v == u) break;            
        }
    }
}
void solve() {
    cin >> n;
    init();
    for(int u = 1; u <= n; u++) {
        int v;
        while(cin >> v) {
            if(v == 0) break;
            adj[u].push_back(v);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            dfs(i, 0);
        }
    }
    if(cnt == 1) {
        cout << 1 << "\n" << 0 << "\n";
        return ;
    }
    vector<int> in(cnt + 1), out(cnt + 1);
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            int x = scc[u], y = scc[v];
            if(x != y) {
                in[y]++;
                out[x]++;
            }
        }
    }
    int ans1 = 0, ans2 = 0;
    for(int i = 1; i <= cnt; i++) {
        if(!in[i]) ans1++;
        if(!out[i]) ans2++;
    }
    cout << ans1 << "\n" << max(ans1, ans2) << "\n";
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
