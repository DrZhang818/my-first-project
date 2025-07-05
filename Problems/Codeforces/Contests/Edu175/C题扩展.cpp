#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2070/problem/C
/*
    DP
    题意:
        给定一个N个单元格组成的长条, 初始颜色为红色, 你可以进行k次以下操作:
        op: 选择一段区间[l,r], 将区间内的单元格染成蓝色
        现给出长度为N的字符串S和数组A
        S[i]表示第i个单元格的正确颜色, B表示蓝色, R表示红色
        A[i]表示第i个单元格不是正确颜色时, 所受到的惩罚
        最终的惩罚为所有生效的A[i]的总和
        要求计算出最小惩罚为多少
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->二分->贪心||DP, 常用优化手段为: 前缀和、双指针、数据结构
        暴力的复杂度在C题原题中已经分析, 是完全无法通过的
        那么本题是否可以二分答案呢? 
            二分答案的要求有两点
            (1)答案具有单调性
            (2)验证答案的时间复杂度低
        对于本题来说, 验证一个答案是否合法并不容易, 并且如果采用背包DP等方法验证会由于
        MX过大而无法通过
        因此走到第三步, 思考贪心 || DP
        我们考虑本题的本质是初始有个初始惩罚tot, 然后选择至多k个区间以减少tot,
        但如果区间覆盖了R, 会出现新的惩罚, 这种特征可以建模为增益数组问题
        如果区间覆盖了B, 增益为+A[i]; 如果覆盖了R, 增益为-A[i]
        我们的问题就转化成在数组中选至多k个不相交的子段, 使得子段和最大
        这是经典的子段和问题, 可以用状态机DP在O(NK)的时间内解决
        (另有用斜率优化的解法, 详见https://www.cnblogs.com/leiyuanze/p/13860835.html)
        我们定义dp[i][j][s] := 前i个数, 至多选k段, 第i个数选/不选的最大子段和
        对于第i个数:
            (1)选, 状态由dp[i - 1][j][1]和dp[i - 1][j - 1][0]得到
                        继承              发展
            (2)不选, 则由dp[i - 1][j][1]和dp[i - 1][j][0]得到
        最后答案就是dp[n][k][0]和dp[n][k][1]中的最大值
        这是能获得的最大增益, 再由tot减掉即可
*/
constexpr ll inf = LLONG_MAX / 2;
void solve() { 
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n + 1);
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(s[i - 1] == 'R') {
            a[i] = -a[i];
        } else {
            tot += a[i];
        }
    }
    vector dp(n + 1, vector<vector<ll>>(k + 1, vector<ll>(2)));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0]) + a[i];
            dp[i][j][0] = max(dp[i - 1][j][1], dp[i - 1][j][0]);
        }
    }
    ll ans = tot - max(dp[n][k][0], dp[n][k][1]);
    cout << ans << "\n";
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
    
