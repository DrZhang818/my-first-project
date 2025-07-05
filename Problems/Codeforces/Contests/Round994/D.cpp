#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2049/problem/D
/*
    动态规划(网格图DP)
    题意:
        给定一个n行m列的网格图, 现在要从(1,1)走到(n,m), 你可以在开始行动前进行若干次操作
        op: 选定某一行, 让这一行的元素向左偏移一次, 代价为k
        操作后, 网格图不可再更改, 你可以每次向右或向下行动, 直到终点
        记操作次数为x
        定义一个合法路径的总代价为k*x + sigma(aij)
        目标是最小化总代价
    关键思考:
        注意到以下性质:
            1.每一行的操作是独立的, 每行的局部最优解不受上一行影响(无后效性)
            2.dp[i][j]可以由dp[i-1][j]和dp[i][j-1]转移吗？
                其中dp[i-1][j]是可以的, 但dp[i][j-1]并不正确
                原因在于dp[i][j-1]是有后效性的
                具体来说, dp[i][j-1]取得最优解时对应的grid[i][j]
                        并不一定是dp[i][j]取得最优解时对应的grid[i][j]
            3.怎么解决2的问题呢？
                可以单独造个temp数组和cur数组
                分别记录转移t次之后的grid数组和对应的(i,j)最优解
                dp[i][j]就在枚举的过程中不断与cur[i][j]+t*k取最小值
                注意！这里的t*k加入的位置很重要
                    这里的t*k放在dp的更新中而不能放在cur的更新中
                    否则就是dp[i-1][j]与cur[i][j-1]+t*k比较, 显然不对了
                    换句话说, t*k是对dp[i-1][j]和cur[i][j-1]共同起作用的
    代码实现时, 可以利用滚动数组, 大幅度优化空间复杂度
    甚至连grid都可以逐行输入, 原因由性质1可知, 行操作无后效性
*/
void solve(){
    int n, m;
    ll k;
    cin >> n >> m >> k;
    vector<ll> grid(m + 1);
    vector<vector<ll>> dp(2, vector<ll>(m + 1, LLONG_MAX / 2));
    auto temp = grid;
    auto cur = dp;
    dp[0][1] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> grid[j];
            dp[i % 2][j] = cur[i % 2][j] = LLONG_MAX / 2; 
        }
        for(int t = 0; t < m; t++){
            for(int j = 1; j <= m; j++){
                temp[j] = grid[(j - 1 + t) % m + 1];
                cur[i % 2][j] = min(dp[(i - 1) % 2][j], cur[i % 2][j - 1]) + temp[j];
                dp[i % 2][j] = min(dp[i % 2][j], cur[i % 2][j] + t * k);
            }   
        }
    }
    cout << dp[n % 2][m] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
