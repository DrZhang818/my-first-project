#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2128/problem/D
/*
    DP || 贪心
    题意:
        给定一个1~N的排列p, 满足对于所有1 <= i <= N-2, 都有max(p[i],p[i+1]) > p[i+2]
        计算所有子数组的最长递减子序列的长度之和
        范围: N∈[3,5e5]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        思考max(p[i],p[i+1]) > p[i+2]的性质
        我们下面证明: 所有以i结尾的子数组的最长下降子序列, 必然以p[i]结尾, 且如果p[i] < p[i-1],
        则倒数第二个数是p[i-1]
        即∀j∈[1,i], [j,i]的最长下降子序列以p[i]结尾, 若p[i]<p[i-1], 结尾前一个数是p[i-1]
        考虑数学归纳法, 假设i成立, 下面思考i+1的情况
        (1)如果j = i+1, [j,i]只有p[i+1], 那么当然是以p[i+1]结尾 
        (2)如果p[i+1] > p[i], 此时必然有p[i-1] > p[i+1] > p[i]:
            这样我们可以把[j,i]的最长下降子序列的结尾p[i]更改为p[i+1]
            由于结尾前一个数是p[i-1], p[i-1] > p[i+1], 因此仍然是合法的最长下降子序列 
            就得到了[j,i+1]的最长下降子序列, 此时以p[i+1]结尾
        (3)如果p[i+1] < p[i]:
            这样我们可以把[j,i]的最长下降子序列的结尾p[i]后面追加p[i+1], 
            就得到了[j,i+1]的最长下降子序列, 此时以p[i+1]结尾, 且结尾前一个数是p[i]
        考虑定义dp[i] := 以p[i]结尾的子序列带来的贡献, 我们令初值为1表示[i,i]本身算作一种
        对于情况(2), 由于是替换p[i], 因此dp[i+1] += dp[i]
        对于情况(3), 由于是在后面追加, 因此dp[i+1] += dp[i] + i
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> dp(n + 1, 1);
    for(int i = 2; i <= n; i++) {
        dp[i] += dp[i - 1];
        if(a[i] < a[i - 1]) {
            dp[i] += i - 1;
        }
    }
    cout << accumulate(dp.begin() + 1, dp.end(), 0LL) << "\n";
}

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
