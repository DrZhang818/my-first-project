#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2114/problem/F
/*
    DP || 数论 || 贪心
    题意:
        给定x,y,k, 你需要最小化以下操作次数, 使得x = y
        op1: 选择一个整数a∈[1,k], 令x = x * a
        op2: 选择一个整数a∈[1,k]且x被a整除, 令x = x / a
        如果x无法变为y输出-1
        范围: x,y,k∈[1,1e6]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 容易想到把x和y做唯一分解后再进行思考
        y分解后的质数中, 指数大于x分解后的需要乘, 小于的需要除
        这件事可以由gcd来做中转, 令g = gcd(x,y)
        则y / g就是要乘的数, x / g就是要除的数, 显然这两部分互相独立, 可以分别计算
        于是问题就变成了: 利用[1,k]中的数字最少需要几个数使得乘积等于x
        这个问题可以通过DP来解决, 我们考虑1变为x的过程, 最多有x的因数数量d(x)个状态
        我们可以定义dp[u] := u最少需要的数量
        则有转移方程dp[u] = min{dp[v] + 1} (v是u的真因子且u / v <= k)
        显然v < u, 因此我们的dp转移顺序应该从小到大进行, 这就需要对因子数组fac进行排序
        这里时间复杂度正确的重要原因是: x的因子数量大约是O(x^(1/3)) ~ O(x^(1/2))
        这样转移虽然是平方级的, 但d(x)量级非常小, 在x <= 1e6情况下, d(x)最大是240
*/
int get(int x, int k) {
    vector<int> fac;
    for(int i = 1; i * i <= x; i++) {
        if(x % i == 0) {
            fac.push_back(i);
            if(i * i < x) {
                fac.push_back(x / i);
            }
        }
    }
    sort(fac.begin(), fac.end());
    int n = fac.size();
    vector<int> dp(n, inf);
    dp[0] = 0;    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(fac[i] % fac[j] == 0 && fac[i] / fac[j] <= k) {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    return dp[n - 1];
}
void solve() {
    int x, y, k;
    cin >> x >> y >> k;
    int g = __gcd(x, y);
    int a = get(x / g, k), b = get(y / g, k);
    if(a == inf || b == inf) {
        cout << -1 << "\n";
    } else {
        cout << a + b << "\n";
    }
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
