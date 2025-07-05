#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://atcoder.jp/contests/abc132/tasks/abc132_f
/*
    DP || 前缀和 || 整除分块
    题意:
        给定两个整数n和lim, 定义一个序列是合法的, 当且仅当序列中任意两个相邻的数的乘积不超过lim
        要求计算出长度为n的合法序列个数
        范围: lim∈[1,1e9], n∈[2,100] 
    关键思考:
        本题是计数类问题, 常用思考方式为: 暴力 -> DP || 贪心, 常用优化手段为: 前缀和 || 数学
        初步分析题意, 我们有个很自然的定义DP方式
        dp[i][j] := 前i个数中, 第i个数选为j的方案数
        状态转移: dp[i][j] = ∑dp[i - 1][k] (k = 1->lim//j)
        这个dp显然可以利用前缀和优化, 只需要我们把dp换种定义方式
        定义dp[i][j] := 前i个数中, 第i个数 ≤ j的方案数
        状态转移: dp[i][j] = dp[i][j-1] + dp[i-1][lim//j]
        但是这样的时间复杂度还是O(n*lim), 
        瓶颈在于lim过大, 需要想办法优化掉
        由于在状态转移的时候涉及到整除, 我们可以把//i的结果进行分块, 根据整除分块理论,
        块数不超过2 * sqrt(lim), 这样时间复杂度就优化到了O(n*sqrt(lim))
        可以用一个数组d记录每个块中存在元素的数量, 同时在预处理d的时候计算出精确的总块数
            注: 块的下标从1开始计数
        这样我们进一步优化了dp的定义
        dp[i][j] := 第i个数为处在块1~j的方案数
        状态转移: dp[i][j] = dp[i][j-1] + d[j] * dp[i - 1][s + 1 - j]
        这里涉及到一个关键的式子:
            当x * y = lim的时候
            x所在的块下标 + y所在的块下标 == s + 1
            因此当我们计算第j个块时, 上一位能选的块最大为第s + 1 - j这个块
*/
const int MOD = 1e9 + 7;
void solve(){
    ll lim;
    int n;
    cin >> lim >> n;
    vector<vector<ll>> dp(2, vector<ll>(2 * sqrt(lim) + 1));
    vector<ll> d(2 * sqrt(lim) + 1);
    ll s = 1;
    for(ll L = 1, R; L <= lim; L = R + 1) {
        R = lim / (lim / L);
        d[s++] = R - L + 1;
        // cout << "s:" << s - 1 << " " << L << "->" << R << "\n";
    }   
    s -= 1;
    for(int i = 0; i < n; i++) {
        auto &cur = dp[i % 2], &pre = dp[(i + 1) % 2];
        for(int j = 1; j <= s; j++) {
            if(i == 0) {
                cur[j] = cur[j - 1] + d[j];
                continue;
            }
            cur[j] = cur[j - 1] + d[j] * pre[s + 1 - j] % MOD;
            cur[j] %= MOD;
        }        
    }
    cout << dp[(n - 1) % 2][s] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

