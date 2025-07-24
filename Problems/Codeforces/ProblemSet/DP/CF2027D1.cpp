#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://codeforces.com/problemset/problem/2027/D1
/*
    DP || 贪心
    题意:
        给定一个长度为N的数组a和一个长度为M的数组b, 起初k的值为1, 你需要通过以下操作使得数组a变为空
        op1: 如果k < m且a非空, 你可以将k的值增加1, 代价为0
        op2: 移除数组a的一个非空前缀, 满足前缀和不超过b[k], 代价为M - k
        你需要求出最小代价, 如果无法使数组a变为空, 输出-1
        范围: N,M∈[1,3e5], N*M∈[1,3e5], a[i],b[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        容易发现, 我们要做的是划分数组, 那么自然想到划分型dp
        定义dp[i][j] := 考虑数组b的前i个数, 移除数组a前j个数的最小代价
        朴素的转移方式为:
        枚举k∈[1,j-1], dp[i][j] = min(dp[i - 1][k] + w(k+1 -> j))
        w(k+1->j)可以通过后缀和统计次数, 乘上单次代价得到
        但是这样有个明显的问题, 时间复杂度是O(n^2*m)的, 超时
        我们考虑贪心剪枝, 我们考虑数组a的最后一次移除
        我们当前在考虑b[i], 因此如果使用i转移的话, 最后一段必然要小于等于b[i]
        贪心地想, 最后一段的和应该要在满足<=b[i]的情况下尽可能大
        因为显然地, dp[i][j - 1] <= dp[i][j]
        那么最后一段尽可能大, 意味着左端点尽可能小
        可以用双指针来找到最后一段的左端点
        这样, 我们就可以缩小k的范围, k只会取一些特殊点, 即某一段的左端点
        进一步地, 我们只需要考虑最后一段即可, 这类似于完全背包的思想
        优化掉第一维后, 就能得到转移方程:
            dp[j] = min(dp[j], dp[j - k] + m - i)
*/
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    int mx = *max_element(a.begin() + 1, a.end());
    if(mx > b[1]) {
        cout << -1 << "\n";
        return;
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<ll> dp(n + 1, inf);
    dp[0] = 0;
    for(int k = 1; k <= m; k++) {
        for(int i = 1, j = 0; i <= n; i++) {
            while(pre[i] - pre[j] > b[k]) {
                j++;
            }
            dp[i] = min(dp[i], dp[j] + m - k);
        }
    }
    cout << dp[n] << "\n";
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
