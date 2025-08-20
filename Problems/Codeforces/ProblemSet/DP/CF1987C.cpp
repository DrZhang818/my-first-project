#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1987/problem/C
/*
    DP
    题意:
        给定一个长度为N的数组, 每秒按从1~N的顺序, 对每个i执行以下操作:
        op: 如果i = n或a[i] > a[i + 1], 则a[i] = max(0, a[i] - 1)
        求至少需要多少秒才能让数组变为全0数组
        范围: N∈[1,1e5], a[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法, 模拟每秒的状态转移, 时间复杂度为O(NM), 超时
        瓶颈在于枚举秒数, 我们需要优化掉O(M)这部分
        观察操作结构, i = n或a[i] > a[i + 1], 这说明a[i]的激活时刻依赖于a[i + 1]
        因此我们考虑倒序dp
        定义dp[i] := a[i:n]变为全0数组的最小时间
        (1)如果a[i] <= a[i + 1]:
            此时a[i + 1]变为0时, 必然有a[i] = 1
            因此dp[i] = dp[i + 1] + 1
        (2)如果a[i] > a[i + 1]:
            此时a[i + 1]变为0时, 必然有a[i] = 1或a[i] >= 2
            如果a[i] = 1, 则dp[i] = dp[i + 1] + 1
            如果a[i] >= 2, 说明在dp[i + 1]秒内, a[i]一直大于a[i + 1], 因此a[i]一直在下降
                则dp[i] = dp[i + 1] + (a[i] - dp[i + 1]) = a[i]
        归纳发现, dp[i] = max(a[i], dp[i + 1] + 1)
        因此可以O(N)时间内递推得到答案
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = a[n];
    for(int i = n - 1; i >= 1; i--) {
        ans = max(a[i], ans + 1);
    }
    cout << ans << "\n";
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
