#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/112692/C
/*
    差分 || 多源BFS最短路
    题意:
        给定一个N×M的矩阵, 其中有k个中心障碍物, 每个中心障碍物有参数(x,y,d):
            中心障碍物位于(x,y), 则a[i][j]都是障碍物, i∈[x-d,x+d],j∈[y-d,y+d]
        定义矩阵中的格子a[i][j]为空格, 当且仅当该格子不是障碍物
        每个空格的权值为: 到所有障碍物的曼哈顿距离的最小值-1
        请你找到权值最大的空格, 输出最大权值, 不存在任何空格输出"-1"
        范围: N∈[1,500], M∈[1,500], K∈[1,500]
        加强范围: N∈[1,3000],M∈[1,3000],K∈[1,1e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考如何把障碍物标记出来, 由于障碍物是一个矩形区域, 因此可以用二维差分实现
        接下来是本题的关键问题: 如何寻找每个障碍物的最短路
        一种思路是把曼哈顿距离转成切比雪夫距离, 这样可以用二分来做到log(n+m)的查询
        总时间复杂度为O((n+m)^2log(n+m))
        更简单高效地是利用多源BFS求出全源最短路
        把每个障碍物当作源头加入队列, 其权值为-1
        接下来就非常简单了, 对于队列中的每个点, 更新它邻接的四个点即可
        如果邻接点已经有权值(已经更新过), 则直接跳过, 否则更新并入队
        这样我们就有了整个图的最短路, 收集答案即可
*/
//优化做法: 转为图论最短路
struct info {
    int x, y;
};
int dir[5] = {-1, 0, 1, 0, -1};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector a(n + 2, vector<int>(m + 2));
    for(int i = 1; i <= k; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        int lx, ly, rx, ry;
        lx = max(1, x - d);
        ly = max(1, y - d);
        rx = min(n, x + d);
        ry = min(m, y + d);
        a[lx][ly] -= 1;
        a[lx][ry + 1] += 1;
        a[rx + 1][ly] += 1;
        a[rx + 1][ry + 1] -= 1;
    }
    vector dis(n + 1, vector<int>(m + 1, inf));
    queue<info> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            if(a[i][j] < 0) {
                dis[i][j] = -1;
                q.push({i, j});
            }
        }
    }
    int ans = -1;
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        ans = max(ans, dis[x][y]);
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || dis[nx][ny] != inf) continue;
            dis[nx][ny] = dis[x][y] + 1;
            q.push({nx, ny});
        }
    }
    cout << ans << "\n";
}


// void solve() {
//     int n, m, k;
//     cin >> n >> m >> k;
//     vector a(n + 2, vector<int>(m + 2));
//     for(int i = 1; i <= k; i++) {
//         int x, y, d;
//         cin >> x >> y >> d;
//         int lx, ly, rx, ry;
//         lx = max(1, x - d);
//         ly = max(1, y - d);
//         rx = min(n, x + d);
//         ry = min(m, y + d);
//         a[lx][ly] += 1;
//         a[lx][ry + 1] -= 1;
//         a[rx + 1][ly] -= 1;
//         a[rx + 1][ry + 1] += 1;
//     }
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
//         }
//     }
//     vector na(n + m + 2, vector<int>(n + m + 2));
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             na[i + j][i - j + m] = a[i][j];
//         }
//     }
//     for(int i = 1; i <= n + m; i++) {
//         for(int j = 1; j <= n + m; j++) {
//             na[i][j] += na[i - 1][j] + na[i][j - 1] - na[i - 1][j - 1];
//         }
//     }
//     auto get = [&](int x, int y) -> int {
//         int lx, ly, rx, ry;
//         int l = -1, r = n + m;
//         while(l + 1 < r) {
//             int mid = l + r >> 1;
//             lx = max(1, x - mid);
//             ly = max(1, y - mid);
//             rx = min(n + m, x + mid);
//             ry = min(n + m, y + mid);
//             if(na[rx][ry] - na[lx - 1][ry] - na[rx][ly - 1] + na[lx - 1][ly - 1] == 0) {
//                 l = mid;
//             } else {
//                 r = mid;
//             }
//         }
//         return l;
//     };
//     int ans = -1;
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             if(a[i][j] == 0) {
//                 ans = max(ans, get(i + j, i - j + m));
//             }
//         }
//     }
//     cout << ans << "\n";
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
