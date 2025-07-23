#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc414/tasks/abc414_f
/*
    图论 || DP || 分层图最短路 || BFS
    题意:
        给定一棵N个顶点的树和一个整数K, 你当前位于顶点1, 你可以进行任意次以下操作:
        op: 选择一个与当前顶点距离为K的顶点, 并移动到该顶点
        对于每个i = 2,3,...,N, 判定能否通过操作移动到顶点i, 如果可以找出最小操作次数
        否则输出-1
        范围: N∈[2,2e5], K∈[1,20]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        对于特殊移动问题, 我们有个经典思路是: 建新图
        但在这里并不适用, 因为新图的边数太多, 考虑K=2时的菊花图, 建新图后变成了N-1阶完全图
        对于N∈[2,2e5], 这样的方式显然是不能接受的
        K的范围很小, 我们要利用到这一性质
        考虑把1次K步拆为K次1步, 这样我们就可以利用dp来解决问题
        dp[i][s] := 到达顶点i, 走了K步中的s步的最小操作次数, s∈[1,K]
        但是这样并不能有效解决问题, 因为在状态转移时会出现问题
        由于我们的路线不能经过重复边, 因此我们还需要记录上一个点是谁
        这样就变成了dp[i][j][s] := 到达顶点i, 上一步为顶点j, 走了K步中的s步的最小操作次数
        然而, 这样的状态量是O(N^2*K), 这是无法接受的
        这里就需要用一个trick, 把边的id作为状态, 一条有向边正好能记录(i,j)的信息
        而边数只有2*(N-1)个, 这样dp[id][s]的空间复杂度为O(NK), 可以存下
        无向图的边编号方法: 把第i条边的的一个方向记为i<<1, 反向记为i<<1|1
        这样就可以通过id ^ 1来访问反向边
        下面考虑状态转移:
        我们开一个rid数组, rid[id] = 编号为id的有向边的终点
        对于当前状态dp[id][s], 记当前所在点为u=rid[id], 上一个点为fa=rid[id^1]
        如果s = K, 那么更新ans[u] = min(ans[u], dp[id][s] / K)
        遍历u的邻居v:
            如果s < K, 那么当前阶段没有结束, 不能访问fa, 因此如果v = fa就跳过
            如果s = K, 那么开启了新一轮, fa是可以到达的
            转移方程为dp[nid][ns] = dp[id][s] + 1
        但这样的转移时间是无法接受的, 每次转移都需要O(度数)
        总复杂度是O(NK*度数), 面对菊花图是O(N^2*K)的转移
        这里再次用到一个trick
        我们开一个vis数组, vis[u][s] := 到达点u, 进行了K步中的s步的次数
        如果vis[u][s] >= 2, 我们就可以跳过更新了
        我们设两次到达分别是从x->u和从y->u
        那么从x->u进行更新时, 会把u的除了x的所有邻居节点进行更新
        从y->u进行更新时, 会把u的除了y的所有邻居节点进行更新
        由于x != y, 因此所有节点都已进行更新, 以后的更新不会发生任何事情, 因此可以跳过

*/
struct edge {
    int v, id;
};
struct info {
    int id, s;
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<edge>> adj(n + 1);
    vector<int> rid(2 * n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v, i << 1);
        adj[v].emplace_back(u, i << 1 | 1);
        rid[i << 1] = v;
        rid[i << 1 | 1] = u;
    }
    vector dp(2 * n, vector<int>(k + 1, -1));
    queue<info> q;
    for(auto [v, id] : adj[1]) {
        dp[id][1] = 1;
        q.push({id, 1});
    }
    vector vis(n + 1, vector<int>(k + 1));
    vector<int> ans(n + 1, inf);
    while(!q.empty()) {
        auto [id, s] = q.front(); q.pop();
        int u = rid[id], fa = rid[id ^ 1];
        if(s == k) ans[u] = min(ans[u], dp[id][s] / k);
        if(vis[u][s] == 2) continue;
        vis[u][s]++;
        for(auto [v, nid] : adj[u]) {
            if(s < k && v == fa) continue;
            int ns = s == k ? 1 : s + 1;
            if(dp[nid][ns] == -1) {
                dp[nid][ns] = dp[id][s] + 1;
                q.push({nid, ns});
            }
        }
    }
    for(int i = 2; i <= n; i++) {
        cout << (ans[i] == inf ? -1 : ans[i]) << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
