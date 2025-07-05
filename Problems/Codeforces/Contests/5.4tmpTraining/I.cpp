#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/gym/105386/problem/I
/*
    后缀和
    题意:
        给定一个长度为N的字符串, 一个字符串是合法的, 当且仅当字符串中每一对相邻的字符都不相同
        定义一个字符串的权值x为: 最少修改x个字符可以使字符串合法
        你可以对字符串进行任意次下列操作: 
        op: 将最左边的字符移动到最右边
        求操作后能得到的字符串最小权值为多少
        范围: n∈[1,5e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法: 共有O(n)种方案, 每个方案需要O(n)时间计算, 时间复杂度为O(n^2), 超时
        通过观察我们发现, 字符串的权值是逐步累积出来的, 可以用后缀和快速计算
        我们可以定义dp[i] := 后缀s[i:]的权值
        则转移方程为dp[i] = dp[i + 1] + (cnt[c] % 2 == 0)
        为方便处理, 我们采取断环成链的方法, 将字符串复制一次
        这样dp[i] - dp[i + n]就是粗略的权值, 只需做一下分类讨论:
        (1)当dp[i + n - 1] = dp[i + n]时, 说明没有发生"进位", 此时算出的就是答案
        (2)当发生进位时, 如(   a)a..., 此时如果(   a)的后缀有奇数个a, 那么答案要-1
            这样的目的是抵消多余进位带来的答案增大效果
        注意特判字符串字符全相同的情况, 此时后缀会无限叠加起来, 导致判断失效
*/
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s += s;
    s = "#" + s;
    vector<int> dp(2 * n + 1), c(2 * n + 1);
    for(int i = 2 * n - 1, cnt = 1; i >= 1; i--) {
        cnt = s[i] == s[i + 1] ? cnt + 1 : 1;
        dp[i] = dp[i + 1] + (cnt % 2 == 0);
    }
    c[1] = 1;
    for(int i = 2; i <= 2 * n; i++) {
        c[i] = s[i] == s[i - 1] ? c[i - 1] + 1 : 1;
    }
    if(c[n] == n) {
        cout << n / 2 << "\n";
        return;
    }
    int ans = inf;
    for(int i = 1; i <= n; i++) {
        if(dp[i + n - 1] == dp[i + n]) {
            ans = min(ans, dp[i] - dp[i + n]);
        } else {
            if(c[i + n - 1] % 2 == 0) {
                ans = min(ans, dp[i] - dp[i + n]);
            } else {
                ans = min(ans, dp[i] - dp[i + n] - 1);
            }
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
