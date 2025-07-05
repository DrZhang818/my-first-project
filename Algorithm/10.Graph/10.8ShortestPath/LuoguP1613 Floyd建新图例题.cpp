#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P1613
/*
    Floyd || 倍增 || DP
    题意:
        给定一个由N个顶点M条有向边构成的图, 每条边的边权为1
        你现在每秒可以移动长度为2^k(k∈N)的距离, 问从顶点1移动到顶点N最少需要几秒
        范围: n∈[2,50], m∈[1,1e4], 数据保证1到N至少有一条路径是2的幂次
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 属于带约束的行动问题, 最终求解的问题也不是传统意义上的最短路
        而是新定义的"秒数", 即最少移动次数
        那么比较自然的想法就是, 预处理每个二元点对能否一次直达, 如果存在路径使得
        i一次移动到j, 那么就把dist(i,j)设为1, 否则设为inf表示不可达
        最终相当于在这个新图上求解1到N的最短路
        这种建新图的手段是带约束移动问题的常用思考方式, 但本题的难点还在于如何建出这个图
        由于涉及2的幂次, 我们可以尝试往倍增上来想一想
        定义dp[i][j][s] := i->j是否存在长为2^s的路径
        我们会发现, 由于原图边权都是1, 意味着任何长度为2^s的路径本质上是由
        2^s个长度为1的路径组成的
        那么就一定存在一个中转点k, 使得dp[i][j][s] = dp[i][k][s-1]+dp[k][j][s-1]
        因此我们只需要记录好初始的dp[i][j][0], 便可以通过递推逐层填充好dp表
        由于涉及到中转点, 本质上是在求解传递闭包问题, 因此可以用Floyd完成内层枚举
        新图建好后, 只需要跑一次最短路就能得到答案了
*/
constexpr ll inf = 1e18;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector dis(n + 1, vector<vector<bool>>(n + 1, vector<bool>(33, false)));
    vector adj(n + 1, vector<ll>(n + 1, inf));
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        dis[u][v][0] = true;
    }
    for(int s = 1; s <= 32; s++) {
        for(int k = 1; k <= n; k++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    if(dis[i][k][s - 1] && dis[k][j][s - 1]) {
                        dis[i][j][s] = true;
                        adj[i][j] = 1;
                    }
                }
            }
        }
    }
    // for(int k = 1; k <= n; k++) {
    //     for(int i = 1; i <= n; i++) {
    //         for(int j = 1; j <= n; j++) {
    //             if(adj[i][k] == inf || adj[k][j] == inf) continue;
    //             adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    //         }
    //     }
    // }
    queue<int> q;
    q.push(1);
    vector<int> dist(n + 1, -1);
    dist[1] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v = 1; v <= n; v++) {
            if(adj[u][v] == 1 && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    cout << dist[n] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
