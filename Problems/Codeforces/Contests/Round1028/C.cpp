#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2116/problem/C
/*
    DP || 数论 || 贪心
    题意:
        给定一个长度为N的数组, 你可以进行以下操作:
        op: 选择一对下标(i,j), 将a[i]替换为gcd(a[i],a[j])
        求最少需要几次操作使得数组所有元素相同
        范围: n∈[1,5000], a[i]∈[1,5000]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质: 显然数组的最终状态是所有元素等于它们的gcd
        设g为数组的gcd, 定义f(x) := 将x转化为g的最少次数
        则问题等价于最小化∑f(a[i]), i∈[1,N]
        显然f函数具有以下性质
        (1)当a[i] = g的时候, f(a[i]) = 0
        (2)当a[i] != g的时候, f(a[i]) >= 1 
        于是, 我们很容易利用性质(2)想到一种贪心策略:
        优先把一个数变成g, 再利用这个数把其他数也变成g
        这样做保证了其他数只用1次就转化成了g, 这是a[i]!=g时f函数的最小值
        那么现在的目标就是让优先哪个数变为g消耗的次数最少
        我们可以先把整个数组除以g, 这样问题就归一化到让哪个数变成1消耗的次数最少
        这个问题可以用DP解决
        定义dp[x] := x变成1的最少操作次数
        而由两个数x,y可以得到gcd(x,y)
        因此有转移方程: dp[gcd(x,y)] = min(dp[gcd(x,y)], dp[x] + dp[y] + 1)
        而gcd(x,y) <= min(x,y), 因此可以保证转移图是个DAG, 且转移顺序为从大到小
        最后答案就是dp[1] + n - 1
        特判dp[1] = 0的情况, 此时答案为a中不为1的个数
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int g = a[1];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        g = __gcd(g, a[i]);
    }
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        a[i] /= g;
        mx = max(mx, a[i]);
    }
    vector<int> dp(mx + 1, inf);
    for(int i = 1; i <= n; i++) {
        dp[a[i]] = 0;
    }
    for(int i = mx; i >= 1; i--) {
        if(dp[i] == inf) continue;
        for(int j = i; j <= mx; j++) {
            if(dp[j] == inf) continue;
            g = __gcd(i, j);
            dp[g] = min(dp[g], dp[i] + dp[j] + 1);
        }
    }
    int ans = dp[1];
    for(int i = 1; i <= n; i++) {
        if(a[i] != 1) {
            ans++;
        }
    }
    if(dp[1] != 0) ans -= 1;
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
