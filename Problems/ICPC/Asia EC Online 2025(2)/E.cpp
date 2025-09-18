#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://qoj.ac/contest/2524/problem/14318
/*
    DP || 组合数学 || 数学
    题意:
        给定N和M, 你需要把0~2^M-1填入到大小为N的数组中, 并满足:
        (1)数组中任意两个相邻元素都不相等
        (2)数组的异或和为0
        范围: N∈[1,1e9], M∈[1,1e9], T∈[1,1e4]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力做法: 枚举所有位置的填法并验证, 时间复杂度为O(2^{MN} * N), 超时
        瓶颈在于不能通过枚举计算, 甚至O(N)的递推也不允许
        我们仔细思考题目条件, 可填的数字是0~2^M-1, 这意味着无论前N-1项怎么填, 我们都能利用第N项使得
        数组异或和为0
        于是, 在条件2作用下, 前N-1项完全决定了第N项, 则问题转化成前N-1项有多少种填法能够满足条件1
        不难发现, 在不考虑第N-1项与第N项重复的情况下, 前N-1项一共有 2^M * (2^M - 1)^{N-2} 种填法
        下面思考如何计算第N-1项与第N项相同的部分, 这部分需要从总方案中去掉
        整个数组异或和为0, 最后两项异或和为0, 这必然导致前N-2项的异或和也为0
        而前N-2项同时符合(1)(2)的方案数恰好就是F(N - 2)
        在2^M * (2^M - 1)^{N-2} 种填法中, 一共有 F(N - 2) * (2^M - 1)种填法的前N-2项异或和为0
        因此有转移方程 dp[i] = 2^M * (2^M - 1)^{i-2} - dp[i - 2] * (2^M - 1)
        然而, 这个方程的求解还是O(N)的, 对于T个测试点, 总复杂度为O(T * N), 超时
        这就需要利用数学技巧: 递推转通项
        观察式子结构:
            f[n] = A*B^{n-2} - B*f[n - 2]
            这是个经典的形式, 我们下面做一些代数变形
            f[n] / B^n = -1/B * f[n - 2] / B^{n-2} + A / B^2
            令g[n] = f[n] / B^n
            g[n] = -g[n - 2] / B + A / B^2
            将其配成等比数列
            g[n] + x = -1/B * (g[n - 2] + x)
            解得 x = -A / B*(B+1)
            由于A = B+1, 因此化简为x = -1/B
            令h[n] = g[n] - 1 / B
            h[n] = -1/B * h[n - 2], 这便是最简形式
            
        显然奇偶项是互相独立的, 我们需要分别进行推导
        (1)n为奇数, 此时有初值f[1] = 1 ⇒ g[1] = 1 / B ⇒ h[1] = 0
            故h[n] = 0
            g[n] = 1 / B
            f[n] = B^{n - 1} = (2^M - 1)^{n - 1}
        (2)n为偶数, 此时有初值f[2] = 0 ⇒ g[2] = 0 ⇒ h[2] = -1 / B
            故h[n] = -1 / B^{n / 2}
            g[n] = (-1/B)^{n / 2} + 1 / B
            f[n] = (-B)^{n / 2} + B^{n - 1} = (1 - 2^M)^{n / 2} + (2^M - 1)^{n - 1}
        利用快速幂, 我们可以在O(T * logn)时间内解决问题
*/

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

int inv(int x) {
    return fast_pow(x, MOD - 2);
}

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int B = fast_pow(2, m) - 1;
    int ans = fast_pow(B, n - 1);
    if(n % 2 == 0) {
        add(ans, fast_pow(MOD - B, n / 2));
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
