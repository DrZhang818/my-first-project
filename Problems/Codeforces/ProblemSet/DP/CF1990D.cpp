#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1990/problem/D
/*
    DP || 贪心
    题意:
        给定一个N×N的网格图, 每行有一个权值a[i], 表示第i行的1~a[i]列为黑色格子, 其余为
        白色格子, 你可以进行以下操作:
        op1: 将一个2×2的矩形区域的格子染成白色
        op2: 将一个1×N的矩形区域的格子染成白色
        注意, op2不能翻转, 换句话说你只能染一行而不能染一列
        请你求出最少需要多少次操作能使所有格子变为白色
        范围: N∈[1,2e5], a[i]∈[0,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察两种操作, 不难发现op2要比op1强大的多, 如果某一行有大量黑色格子, 毫无疑问我们要选op2
        那么直接用N次op2就一定最优吗? 显然也不是
        假如网格图正好就剩一个2×2的区域是黑色, 那么直接一次op1就干掉了
        所以二者有没有一个可贪心的边界呢?
        我们试想, 如果第i行有 >= 5个黑色格子, 我们可以断定此时用op2是更优的
        因为我们如果用op1来覆盖这5个格子, 至少要操作3次, 而产生的增量收益只会对i-1行和i+1行产生影响
        那此时替换成对i-1,i,i+1进行三次op2, 也是操作3次, 但把这三行全部消除了! 这显然更优
        因此我们真正要决策的是对于 <= 4的情况, 如何进行操作
        此时状态数就很少了, 我们可以直接分类讨论, 分成8种情况写个轮廓线dp即可解决
        但这样转移有些复杂, 我们事实上可以进一步贪心优化
        我们注意到, 对于i和i+1这两行, 最多放置一个同时作用于i和i+1的op1
        这很容易论证, 假设有两个op1作用于这两行, 那我们直接替换成2次op2, 就能直接消除这两行, 显然更优
        因此, 我们可以这样定义:
        f(i) := 完美解决前i行的最小操作次数
        g(i) := 解决前i行, 且覆盖了a[i + 1][1]和a[i + 1][2]的次数
        这样状态转移就很简单了, 我们考虑刷表法
        当前处于第i行, 我们考虑如何转移到第i + 1行
        (0)如果i + 1行没有黑色格子, f[i + 1] = f[i]
        (1)直接用op2干掉i + 1行, f[i + 1] = f[i] + 1
        (2)如果i + 1行的黑色格子 <= 2:
            我们可以用g[i]更新i + 1, f[i + 1] = min(f[i + 1], g[i])
            同时, 也可以用op1作用i + 1, g[i + 1] = min(g[i + 1], f[i] + 1)
        (3)如果i + 1行的黑色格子 <= 4:
            此时只有i + 2行的黑色格子 <= 4才有意义, 即这种情况
            1 1
            1 1 1 1
            1 1 1 1
            1 1
            这时候我们可以用3次操作染掉这些格子
            g[i + 2] = min(g[i + 2], g[i] + 2)
        最后答案为f[n]
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> f(n + 1, inf), g(n + 1, inf);
    f[0] = 0;
    for(int i = 0; i < n; i++) {
        f[i + 1] = min(f[i + 1], f[i] + (a[i + 1] > 0));
        if(a[i + 1] <= 2) {
            f[i + 1] = min(f[i + 1], g[i]);
            g[i + 1] = min(g[i + 1], f[i] + 1);
        }
        if(i + 2 <= n && a[i + 1] <= 4 && a[i + 2] <= 4) {
            g[i + 2] = min(g[i + 2], g[i] + 2);
        }
    }
    cout << f[n] << "\n";
}

// void solve() {
//     int n;
//     cin >> n;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     int ans = 0;
//     vector<array<int, 8>> dp(n + 1, {inf,inf,inf,inf,inf,inf,inf,inf});
//     dp[0][0] = 0;
//     for(int i = 1; i <= n; i++) {
//         int mn = *min_element(dp[i - 1].begin(), dp[i - 1].end());
//         dp[i][0] = min({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2], dp[i - 1][5]});
//         dp[i][1] = min({dp[i - 1][0] + 1, dp[i - 1][1] + 1, dp[i - 1][2] + 1, dp[i - 1][3], dp[i - 1][5] + 1, dp[i - 1][7]});
//         dp[i][2] = min({dp[i - 1][0] + 2, dp[i - 1][1] + 2, dp[i - 1][2] + 2, dp[i - 1][3] + 1, dp[i - 1][4], dp[i - 1][5] + 2, dp[i - 1][6] + 1, dp[i - 1][7] + 1});
//         dp[i][3] = min({dp[i - 1][0] + 1, dp[i - 1][1] + 1, dp[i - 1][2] + 1, dp[i - 1][3] + 1, dp[i - 1][5] + 1, dp[i - 1][7] + 1});
//         dp[i][4] = mn + 2;
//         dp[i][5] = mn + 1;
//         dp[i][6] = min({dp[i - 1][0] + 2, dp[i - 1][1] + 2, dp[i - 1][2] + 2, dp[i - 1][3] + 1, dp[i - 1][4] + 1, dp[i - 1][5] + 2, dp[i - 1][6] + 2, dp[i - 1][7] + 1});
//         dp[i][7] = min({dp[i - 1][0] + 2, dp[i - 1][1] + 2, dp[i - 1][2] + 2, dp[i - 1][3] + 2, dp[i - 1][4] + 1, dp[i - 1][5] + 2, dp[i - 1][6] + 1, dp[i - 1][7] + 2});
//         if(a[i] > 0) dp[i][0] = inf;
//         if(a[i] > 2) dp[i][1] = dp[i][3] = inf;
//         if(a[i] > 4) dp[i][2] = dp[i][4] = dp[i][6] = dp[i][7] = inf;
//     }
//     ans = *min_element(dp[n].begin(), dp[n].end());
//     cout << ans << "\n";
// }

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
