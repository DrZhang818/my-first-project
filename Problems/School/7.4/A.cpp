#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc149/tasks/abc149_a
/*
    贪心
    题意:
        给定一个长度为N的字符串和一个整数K, 字符串由'r''s''p'组成, 代表对手的出招顺序
        'r'代表石头, 's'代表剪刀, 'p'代表布
        给定三个整数r,s,p, 表示分别自己表示出石头、剪刀、布战胜对手时获得的分数
        由于你知道了对手的出招顺序, 为了公平性, 你的第i轮的出招不能与第i-k轮的出招一致
        求出你最多可以获得多少分数
        范围: N∈[2,1e5], K∈[1,N-1], r,s,p∈[1,1e4]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 看起来很像一道dp题目, 但事实是一个简单的贪心题
        我们可以按照模K对整个字符串做一个划分, 得到K个子序列
        对于不同子序列之间是互不影响的, 因此我们只需要单独考虑某个子序列的决策即可
        在同一个子序列中, 我们容易发现以下性质:
            能赢就赢是最优的
        这很容易通过交换论证证明
        设a[i] = a[i+1], 且a[i]可选
        那么选a[i]或a[i+1]得到的贡献是相同的
        但选a[i]不会对a[i+2]及以后产生影响, 但a[i+1]会限制a[i+2]的选择
        显然a[i]和a[i+1]都不选也是劣的
        因此选a[i]必然最优
*/
//优化解法 贪心
void solve() {
    int n, k;
    cin >> n >> k;
    int r, s, p;
    cin >> r >> s >> p;
    string t;
    cin >> t;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(t[i] == 's') ans += r;
        if(t[i] == 'p') ans += s;
        if(t[i] == 'r') ans += p;
        if(i + k < n && t[i + k] == t[i]) t[i + k] = 'f';
    }
    cout << ans << "\n";
}


// void solve() {
//     int n, k;
//     cin >> n >> k;
//     vector<int> w(3);
//     cin >> w[0] >> w[1] >> w[2];
//     string t;
//     cin >> t;
//     t = "#" + t;
//     ll ans = 0;
//     for(int i = 1; i <= k; i++) {
//         vector<array<int,3>> dp(n / k + 5);
//         int cnt = 0;
//         for(int j = i; j <= n; j += k) {
//             int cur;
//             if(t[j] == 'r') cur = 0;
//             if(t[j] == 's') cur = 1;
//             if(t[j] == 'p') cur = 2;
//             int nxt = (cur + 2) % 3;
//             if(cnt == 0) {
//                 dp[cnt][nxt] = w[nxt];
//             } else {
//                 dp[cnt][nxt] = max(dp[cnt - 1][(nxt + 1) % 3], dp[cnt - 1][(nxt + 2) % 3]) + w[nxt];
//                 dp[cnt][(nxt + 1) % 3] = max(dp[cnt - 1][(nxt + 2) % 3], dp[cnt - 1][nxt]);         
//                 dp[cnt][(nxt + 2) % 3] = max(dp[cnt - 1][(nxt + 1) % 3], dp[cnt - 1][nxt]);               
//             }
//             cnt++;
//         }
//         ans += *max_element(dp[cnt - 1].begin(), dp[cnt - 1].end());
//     }
//     cout << ans << "\n";
// }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
