#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://atcoder.jp/contests/abc113/tasks/abc113_d
/*
    DP
    题意:
        给定M条并排的竖线, 每条竖线有N个槽位, 从上到下编号为1~N
        你可以在相邻竖线的相同编号的槽位上摆放一根水平木棒, 这将同时占用两条竖线各自的槽位
        每个槽位最多只能被一根木棒占有, 换句话说, 不能有两个木棒贴在一起
        摆放完木棒后, 一个小球会从第1条竖线的顶部降落, 如果碰到木棒, 就会沿着木棒水平移动, 
        否则竖直降落
        给定一个整数K, 求有多少种方案可以使小球最终到达第K条竖线的底部(第K条竖线的第N个槽位的正下方)
        结果对1000000007取模
        范围: N∈[1,100], M∈[1,8], K∈[1,M]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察题目性质, 由于M非常小, 所以我们的第一反应应该是暴力枚举
        M条竖线, 在同一行会产生M-1个空位
        每个空位只有选或不选两种状态, 因此我们可以用二进制来枚举第i行的状态
        行间是无任何影响的, 我们发现只需关心i-1行有多少种方案使得球从第j条竖线降落即可
        定义dp[i][j] := 考虑前i-1行, 小球最终从第j条竖线降落的方案数
        枚举合法状态(这可以预处理)
        在状态为s的情况下, 我们从左到右枚举第j个竖线
        (1)如果s >> j & 1 = 1, 意味着第j和j+1竖线间搭建了木棒
            则dp[i][j] = dp[i-1][j+1]
              dp[i][j+1] = dp[i-1][j]
              同时手动让j++, 表示下一位置跳过转移
        (2)如果s >> j & 1 = 0
            则dp[i][j] = dp[i-1][j]
        最后的答案为dp[n][k-1]
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    k--;
    vector<int> a;
    for(int s = 0; s < 1 << m - 1; s++) {
        if(s & s << 1) continue;
        a.push_back(s);
    }
    vector<int> dp(m + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        vector<int> ndp(m + 1);
        for(int s : a) {
            for(int j = 0; j <= m - 1; j++) {
                if(s >> j & 1) {
                    add(ndp[j], dp[j + 1]);
                    add(ndp[j + 1], dp[j]);
                    j++;
                } else {
                    add(ndp[j], dp[j]);
                }
            }
        }
        swap(dp, ndp);
    }
    cout << dp[k] << "\n";
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
