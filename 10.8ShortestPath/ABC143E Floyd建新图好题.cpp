#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://atcoder.jp/contests/abc143/tasks/abc143_e
/*
    Floyd || DP
    题意:
        给定一个由N个顶点M条无向有权边, 车的油箱容量为L, 当行驶到一个顶点时可以选择
        加满油箱或者什么都不做, 每行驶一单位距离消耗一单位的油
        现有Q次询问, 每次询问给定两个顶点S和T, 初始油箱为满, 回答从S到T至少要加几次油
        若无法到达, 回答-1
        范围: N∈[2,300], M∈[0,N(N-1)/2], w,L∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先分析问题的性质, 会发现这属于带约束的移动问题, 最短路由距离最短变成次数最少
        考虑经典的建新图方式, 预处理每个二元点对能否一次直达, 如果存在路径使得
        dist(u,v) <= L, 那么新图中(u,v)的权值设为1, 否则为inf
        因此就可以利用floyd跑出全源最短路后逐一连边即可
        最后在得到的新图中再求一次全源最短路, 即可O(1)时间回答询问
        预处理时间为O(N^3), 可以通过
*/
constexpr ll inf = 1e18;
void solve() { 
    int n, m;
    ll L;
    cin >> n >> m >> L;
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, inf));
    for(int i = 1; i <= n; i++) dis[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dis[i][k] == inf || dis[k][j] == inf) continue;
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, 1000000000));
    for(int i = 1; i <= n; i++) {   
        for(int j = 1; j <= n; j++) {
            if(dis[i][j] <= L) {
                adj[i][j] = 1;
            }
        }
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        if(adj[u][v] == 1000000000) cout << -1 << "\n";
        else cout << adj[u][v] - 1 << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
    