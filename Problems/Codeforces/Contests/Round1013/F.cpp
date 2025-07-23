#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://codeforces.com/problemset/problem/2091/F
/*
    DP || 前缀和
    题意:
        有一个大小为N×M的攀岩墙, 其中一些格子包含岩点, 定义合法路线为:
        (1)路线起点位于最底层(第N行)
        (2)路线终点位于最顶层(第1行)
        (3)每个后续岩点不得低于前一个岩点
        (4)每个层级至少使用一个岩点(即矩阵的每一行)
        (5)每个层级最多使用两个岩点(因为你只有两只手)
        (6)当前岩点到下一个岩点的转移需满足: 两个点的欧几里得距离不超过你的臂展
        给定你的臂展为d, 请你求出所有合法路线的数量, 当两条路线使用的岩点列表或访问顺序不同
        即视为不同路线, 结果对998244353取模
        范围: N∈[2,2000], M,d∈[1,2000]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数据结构
        对于这种多条件的题目, 我们先隔离一些条件, 思考简单情况
        假设每次必须选择上一层的岩点, 不选择同层的岩点
        这时就变成了经典的前缀和优化dp的问题
        由于我们的臂展为d, 那么上一层能选到的点为[x-d+1,x+d-1], 我们可以预处理上一层的
        前缀和数组, 然后S[x+d-1] - S[x-d]就是从当前点出发的路线数量
        按照这种方式, 我们能从第i行转移到第i+1行, 得到第i+1行的初步结果
        考虑同层的一次移动后, 我们还要做进一步的计算
        在当前层, 能选到的点为[x-d,x+d], 于是可以做进一步的前缀和preS
        则S[x] = preS[x+d] - preS[x-d-1]
        这样就完成了第二次更新, 我们就得到了正确的方案数
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() { 
    int n, m, d;
    cin >> n >> m >> d;
    int r = d - 1;
    vector a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> dp(m + 1);
    for(int i = 1; i <= n; i++) {
        vector<int> ndp(m + 1);
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != 'X') continue;
            if(i == 1) ndp[j] = 1;
            else ndp[j] = (dp[min(m, j + r)] - dp[max(0, j - r - 1)] + MOD) % MOD;
        }
        vector<int> pre(m + 1);
        for(int j = 1; j <= m; j++) {
            pre[j] = (pre[j - 1] + ndp[j]) % MOD;
        }
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == 'X') {
                ndp[j] = (pre[min(m, j + d)] - pre[max(0, j - d - 1)] + MOD) % MOD;
            }
        }
        for(int j = 1; j <= m; j++) {
            add(ndp[j], ndp[j - 1]);
        }
        swap(dp, ndp);
    }    
    cout << dp[m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
