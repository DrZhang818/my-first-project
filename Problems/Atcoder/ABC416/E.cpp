#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/abc416/tasks/abc416_e
/*
    最短路 || DP
    题意:
        给定一个N个节点M条边的无向带权图, 其中有K个节点设有机场
        给定一个整数T, 任意两个机场之间额外有一条权值为T的边
        你需要回答Q次查询:
        q1: 给定x,y,t, 在节点x,y间新建一条权值为t的边
        q2: 给定x, 在节点x设置机场
        q3: 求解∑∑dis(i,j), i∈[1,N],j∈[1,N], dis(i,j)表示i,j间的最短路
            如果i和j不连通, 则dis(i,j) = 0
        范围: N∈[1,500], M∈[0,1e5], 所有边权∈[1,1e9], K∈[0,N], Q∈[1,1000]
    关键思考:
        本题为数据结构类题目, 需要读请题目, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先我们明确一件事: 现代计算机1s的计算量应按照5e8来估算, 本题时限为3.5s
        询问3是个典型的全源最短路, 观察到N范围不大, 因此考虑使用Floyd算法
        首先跑一次N^3的Floyd, 预处理出全源最短路
        问题在于如何维护带修的Floyd呢
        q1是经典的修改单条边的Floyd, 我们枚举所有点对(i,j), 看dis(i,j)是否小于dis(i,x)+w+dis(y,j)
        以及dis(i,y) + w + dis(x,j), 即可在O(N^2)时间内完成更新
        q2是本题难点, 相当于添加了很多条边, 这时不能再按照q1的方式逐个更新了
        好在所有机场之间传送的时间相同, 因此我们可以采用建新点的方式
        引入一个辅助节点N + 1, 我们设当前新设的机场为o
        我们可以让机场->机场变为机场->N+1->机场
        其中机场->N+1的边权定为T, N+1->机场的边权定为0
        这样q2又变成了修改单条边了, 与q1解决方式相同      
*/
void solve() {
    int n, m;
    cin >> n >> m;
    vector dis(n + 2, vector<ll>(n + 2, inf));
    for(int i = 1; i <= n + 1; i++) {
        dis[i][i] = 0;
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }
    int k, t;
    cin >> k >> t;
    for(int i = 1; i <= k; i++) {
        int o;
        cin >> o;
        dis[o][n + 1] = t;
        dis[n + 1][o] = 0;
    }
    for(int o = 1; o <= n + 1; o++) {
        for(int i = 1; i <= n + 1; i++) {
            if(dis[i][o] == inf) continue;
            for(int j = 1; j <= n + 1; j++) {
                if(dis[o][j] == inf) continue;
                if(dis[i][j] > dis[i][o] + dis[o][j]) {
                    dis[i][j] = dis[i][o] + dis[o][j];
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(dis[i][j] == inf) continue;
            ans += dis[i][j];
        }
    }
    auto work = [&](int x, int y, int w) -> void {
        for(int i = 1; i <= n + 1; i++) {
            if(dis[i][x] == inf) continue;
            for(int j = 1; j <= n + 1; j++) {
                if(dis[y][j] == inf) continue;
                if(dis[i][j] > dis[i][x] + w + dis[y][j]) {
                    if(dis[i][j] != inf && i <= n && j <= n) ans -= dis[i][j];
                    dis[i][j] = dis[i][x] + w + dis[y][j];
                    if(i <= n && j <= n) ans += dis[i][j];
                }
            }
        }
    };
    int q;
    cin >> q;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int u, v, w;
            cin >> u >> v >> w;
            if(w >= dis[u][v]) continue;
            work(u, v, w);
            work(v, u, w);
        } else if(op == 2) {
            int o;
            cin >> o;
            work(o, n + 1, t);
            work(n + 1, o, 0);
        } else {
            cout << ans << "\n";
        }
    } 
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
