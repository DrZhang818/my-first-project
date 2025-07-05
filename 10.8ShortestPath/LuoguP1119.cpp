#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P1119
/*
    Floyd最短路
    题意:
        给定N个节点, M条无向有权边, 每个节点有一个时间戳t, 代表节点在t时刻及以后是有效的
        一条边可以经过, 当且仅当它连接的两个节点全部有效
        现在有Q条询问, 每条询问为一个三元组(u, v, t), 你需要回答在t时刻u到v的合法最短路
        合法路径所经过的边必须是"可经过的", 如果不存在任何一条合法路径, 回答-1
        数据保证节点的时间戳t, 询问的时刻t按照升序给出
        范围: N∈[1,200], M∈[0,N(N-1)/2], Q∈[1,5e4], 所有输入的整数不超过1e5
    关键思考:
        本题是数据结构类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        
*/
constexpr ll inf = 1e18;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> tm(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> tm[i];
    }
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, inf));
    for(int i = 1; i <= n; i++) dis[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u++;
        v++;
        dis[u][v] = dis[v][u] = w;
    }
    int q;
    cin >> q;
    int idx = 1;
    for(int i = 1; i <= q; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u++;
        v++;
        if(tm[u] > t || tm[v] > t) {
            cout << -1 << "\n";
            continue;
        }
        while(idx <= n && tm[idx] <= t) {
            int u = idx;
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][u] + dis[u][j]);
                }
            }
            idx++;
        }
        cout << (dis[u][v] == inf ? -1 : dis[u][v]) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
