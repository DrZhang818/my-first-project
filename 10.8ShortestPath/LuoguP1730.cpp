#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P1730
/*
    拓扑排序 || DP
    题意:
        给定一个N个点M条边的带权DAG, 定义路径密度为: 路径上的权值和除以边数
        现在有Q次询问, 每次询问给出两个点x和y, 求出x到y密度最小的路径
        如果不存在通路, 输出"OMG!"
        范围: N∈[1,50], M∈[1,1000], W∈[1,1e5], Q∈[1,1e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        考虑题目是个dag, 我们可以求出topo序后, 在拓扑序上进行思考
        对于单次询问, 我们可以把x->y的路径按照边数进行划分
        定义f(i,j) := 从i到出发经过j条边到达y的最小权值和
        则有转移方程: f(i,j) = min{ f(i的后继, j - 1) + w[i][i的后继] }
        答案就是min{ f(x,j) }
        借助这种方法, 我们可以在O(N^3)的时间内处理单次询问, 总复杂度为O(N^3 * Q)
        虽然由于常数系数较小可以通过, 但不是最优方案, 我们可以考虑预处理
        定义g[i][j] := 从i到j的最小密度
        我们可以枚举每个i∈[1,N], 从第i个点开始拓扑排序, 对能访问到的点进行更新即可
        最终可以在O(N^4 + Q)的时间内回答所有询问
        特别提醒: 本题有重边, 需要对重边进行处理
*/
void solve() {
    int n, m;
    cin >> n >> m;
    vector adj(n + 1, vector<int>(n + 1));
    vector<int> deg(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(!adj[u][v]) adj[u][v] = w;
        else adj[u][v] = min(adj[u][v], w);
    }
    vector ans(n + 1, vector<db>(n + 1, inf));
    vector<bool> vis(n + 1);
    auto init = [&](auto &&self, int u) -> void {
        for(int v = 1; v <= n; v++) {
            if(adj[u][v]) {
                deg[v]++;
                if(!vis[v]) self(self, v);
                vis[v] = true;
            }
        }
    };  
    auto topo = [&](int x) -> void {
        for(int i = 1; i <= n; i++) vis[i] = false;
        init(init, x);
        vector dp(n + 1, vector<int>(n + 1, inf));
        dp[x][0] = 0;
        queue<int> q;
        q.push(x);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v = 1; v <= n; v++) {
                if(adj[u][v]) {
                    if(--deg[v] == 0) {
                        q.push(v);
                    }
                    for(int j = 1; j <= n; j++) {
                        dp[v][j] = min(dp[v][j], dp[u][j - 1] + adj[u][v]);
                    }
                }
            }
            for(int i = 1; i <= n; i++) {
                if(dp[u][i] != inf) {
                    ans[x][u] = min(ans[x][u], (db)dp[u][i] / i);
                }
            }
        }
    };
    for(int i = 1; i <= n; i++) topo(i);
    int q;
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        if(ans[x][y] > inf - 1) {
            cout << "OMG!\n";
        } else {
            cout << fixed << setprecision(3) << ans[x][y] << "\n";
        }
    }
}


// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector<vector<int>> adj(n + 1, vector<int>(n + 1, inf));
//     vector<int> deg(n + 1);
//     for(int i = 1; i <= m; i++) {
//         int u, v, w;
//         cin >> u >> v >> w;
//         if(adj[u][v] == inf) {
//             adj[u][v] = w;
//             deg[v]++;
//         } else {
//             adj[u][v] = min(adj[u][v], w);
//         }
//     }
//     queue<int> q;
//     for(int i = 1; i <= n; i++) {
//         if(!deg[i]) {
//             q.push(i);
//         }
//     }
//     vector<int> a{0};
//     vector<int> id(n + 1);
//     a.reserve(n + 1);
//     while(!q.empty()) {
//         int u = q.front(); q.pop();
//         id[u] = a.size();
//         a.push_back(u);
//         for(int v = 1; v <= n; v++) {
//             if(adj[u][v] != inf) {
//                 if(--deg[v] == 0) {
//                     q.push(v);
//                 }
//             }
//         }
//     }
//     auto cal = [&](int x, int y) -> db {
//         x = id[x], y = id[y];
//         if(x > y) return -1;
//         vector<vector<int>> dp(n + 1, vector<int>(n, inf));
//         dp[y][0] = 0;
//         for(int i = y - 1; i >= x; i--) {
//             int u = a[i];
//             for(int j = i + 1; j <= y; j++) {
//                 int v = a[j];
//                 if(adj[u][v] == inf) continue;
//                 for(int k = 1; k <= y - j + 1; k++) {
//                     dp[i][k] = min(dp[i][k], dp[j][k - 1] + adj[u][v]);
//                 }
//             }
//         }
//         db ans = inf;
//         for(int i = 1; i <= n - 1; i++) {
//             if(dp[x][i] != inf) {
//                 ans = min(ans, (db)dp[x][i] / i);
//             }
//         }
//         return ans > inf - 1 ? -1 : ans;
//     };
//     int Q;
//     cin >> Q;
//     while(Q--) {
//         int x, y;
//         cin >> x >> y;
//         db ans = cal(x, y);
//         if(ans < -0.5) {
//             cout << "OMG!\n";
//         } else {
//             cout << fixed << setprecision(3) << ans << "\n";
//         }
//     }
// }

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
