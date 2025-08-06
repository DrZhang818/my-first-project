#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://acm.hdu.edu.cn/showproblem.php?pid=1052
/*
    DP || 贪心
    题意:
        田忌和齐王在赛马, 二人各有N匹马, 田忌每匹马战力为a[i], 齐王每匹马战力为b[i]
        两匹战力分别为x,y的马在比赛时, 战力高的马总是获胜, 战胜方获得200得分, 战败方减少200得分
        如果两匹马战力相同, 那么双方打为平手, 得分不发生变化
        田忌已知齐王的出马顺序, 他想通过调整自己的出马顺序最大化自己的得分, 请你算一算田忌最多能得多少分
        范围: N∈[1,1000], a[i],b[i]∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        我们把齐王的马按照战力从高到低进行排序, 不失一般性地, 假设齐王就按这种顺序进行出马
        对于齐王的第i个马, 如果我们当前剩余的马中可以战胜它, 那么贪心地想, 一定就去战胜这匹马
        如果我们剩余的马中都会被它击败, 那么贪心地想, 我们一定取战力最小的马去迎战, 这样损失更小
        困难的点在于, 如果我们战力最高的马会与它打为平手, 此时该如何决策呢?
        这时无论我们是贪心地打平手 还是 贪心地取最小的马, 都会遇到反例
        但我们发现, 我们的决策只有选最大和选最小两种
        因此选完之后, 剩下的部分仍然是个连续的区间
        这样我们就有了区间dp的思路
        我们把田忌的马也按从大到小排序
        dp[i][j] := 田忌的编号i~编号j的马, 应战齐王的后N - (j-i)匹马, 能得到的最大得分
        那么令x = N - j + i
        有转移方程:
            dp[i][j] = max(dp[i + 1][j] + cal(a[i],x), dp[i][j - 1] + cal(a[j], x))
        边界情况:
            dp[i][i] = cal(a[i], x)
        答案为:
            dp[1][N]
*/
int cal(int x, int y) {
    if(x > y) return 200;
    if(x < y) return -200;
    return 0;
}
int n;
void solve() {
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    sort(b.begin() + 1, b.end(), greater<int>());
    vector dp(n + 1, vector<int>(n + 1));
    for(int k = 1; k <= n; k++) {
        int x = b[n - k + 1];
        for(int i = 1; i + k - 1 <= n; i++) {
            int j = i + k - 1;
            if(i == j) {
                dp[i][j] = cal(a[i], x);
            } else {
                dp[i][j] = max(dp[i + 1][j] + cal(a[i], x), dp[i][j - 1] + cal(a[j], x));
            } 
        }
    }
    cout << dp[1][n] << "\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n) {
        if(n == 0) break;
        solve();
    }
    return 0;
}
