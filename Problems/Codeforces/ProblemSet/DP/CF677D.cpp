#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/677/problem/D
/*
    DP || 数据结构
    题意: 
        给定一个N×M的矩阵, 每个格子都有一个宝箱, 宝箱类型为a[i][j]
        每个x <= p-1型宝箱中都有一把能打开任意x + 1型宝箱的钥匙, 所有1型宝箱都未上锁
        矩阵中恰好有一个p型宝箱
        你每次可以向上下左右四个方向移动一格, 并使行走总距离 + 1
        请你求出从(1,1)出发, 解开p型宝箱所需行走的最小总距离是多少?
        范围: N,M∈[1,300], p∈[1,NM], 保证对于1~p之间的每个x, 至少存在一个x型宝箱
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        由于拓扑序很明显, 我们非常容易想到O(N^2 * M^2 / p)的暴力做法
        按照类型对宝箱进行分组, 暴力地从类型i的所有宝箱更新到类型i+1的所有宝箱
        这样每两个类型之间均摊下来需要O(N^2 * M^2 / p^2)的时间, 总共有p - 1层, 复杂度为O(N^2 * M^2 / p)
        令dp[i][j] := 解开第i型的第j个宝箱所需要的最小步数        
        观察转移式子:
            dp[i][j] = min({dp[i-1][k] + |x - xk| + |y - yk|})
        如果我们把绝对值拆开, 能否简化问题呢?
        不妨考虑x >= xk, y >= yk的情况
        对于这些k, dp[i][j] = min({dp[i - 1][k] + x + y - xk - yk})
                           = min({dp[i - 1][k] - xk - yk}) + x + y
        我们神奇地将当前点(x,y)从转移式中分离开了
        对于min({dp[i - 1][k] - xk - yk}), xk <= x, yk <= y这个式子, 可以用二维树状数组进行维护
        注意: 二维树状数组里面, for循环必须新设循环变量i,j, 不能直接用x, y
        树状数组可以维护前缀最小值, 那对于xk <= x这样的查询, 我们要查的是后缀最小值, 该如何做呢?
        这可以用一个trick, 把x变为n - x + 1, 就转化成维护前缀最小值了
*/
void chmin(int &x, int y) {
    if(x > y) {
        x = y;
    }
}
inline int lowbit(int o) { return o & -o; }
class BIT {
    vector<vector<int>> tr;
    int n, m;
public:
    BIT(int a, int b) : tr(a + 1, vector<int>(b + 1, inf)), n(a), m(b){}
    void add(int x, int y, int d) {
        for(int i = x; i <= n; i += lowbit(i)) {
            for(int j = y; j <= m; j += lowbit(j)) {
                chmin(tr[i][j], d);
            }
        }
    }
    void clear(int x, int y) {
        for(int i = x; i <= n; i += lowbit(i)) {
            for(int j = y; j <= m; j += lowbit(j)) {
                tr[i][j] = inf;
            }
        }
    }
    int query(int x, int y) {
        int res = inf;
        for(int i = x; i > 0; i -= lowbit(i)) {
            for(int j = y; j > 0; j -= lowbit(j)) {
                chmin(res, tr[i][j]);
            }
        }
        return res;
    }
};
struct info {
    int x, y, d;
};
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<info>> a(p + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            a[x].emplace_back(i, j, inf);
        }
    }
    a[0].emplace_back(1, 1, 0);
    vector<BIT> tr(4, BIT(n, m));
    for(int i = 1; i <= p; i++) {
        for(auto [x, y, d] : a[i - 1]) {
            tr[0].add(x, y, d - x - y);
            tr[1].add(n - x + 1, y, d + x - y);
            tr[2].add(x, m - y + 1, d - x + y);
            tr[3].add(n - x + 1, m - y + 1, d + x + y);
        }
        for(auto &[x, y, d] : a[i]) {
            chmin(d, tr[0].query(x, y) + x + y);
            chmin(d, tr[1].query(n - x + 1, y) - x + y);
            chmin(d, tr[2].query(x, m - y + 1) + x - y);
            chmin(d, tr[3].query(n - x + 1, m - y + 1) - x - y);
        }
        for(auto [x, y, d] : a[i - 1]) {
            tr[0].clear(x, y);
            tr[1].clear(n - x + 1, y);
            tr[2].clear(x, m - y + 1);
            tr[3].clear(n - x + 1, m - y + 1);
        }
    }
    cout << a[p][0].d << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
