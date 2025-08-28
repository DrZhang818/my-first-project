#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://atcoder.jp/contests/abc258/tasks/abc258_h
/*
    DP || 矩阵
    题意:
        给定一个长度为N的数组a和一个整数S
        定义一个序列是合法的, 当且仅当序列满足以下条件:
        (1)序列中每一项都是正奇数 
        (2)序列的所有项之和为S
        (3)序列的每个前缀和都不能与a中的任何一个元素相等
        求合法序列数量, 结果对998244353取模
        范围: N∈[1,1e5], 1 <= a[1] < a[2] <...< a[N] < S <= 1e18
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        对于这种多条件问题, 我们可以先忽略一部分条件, 考虑题目的easy版本:
        我们忽略条件(3), 思考在满足(1)(2)的情况下如何进行计数?
        由于每项都是正数, 因此前缀和序列是递增的, 并且有一个关键性质:
            每个序列X与它的前缀和序列Y是一一对应的
        当我们从前缀和视角思考问题后, 题目就变成一个选数问题:
            从{0,1,...,S}中选出任意个数字, 并满足0和S必选, 且选出的数字升序排列后
            相邻两项一奇一偶
        有多少种选数方案, 就有多少种前缀和序列, 就对应多少种合法序列X
        我们考虑这种状态机dp:
            dp[i][s] := 考虑前i个数字, 最后一次选的数与s奇偶性相同的方案数
                        其中s∈{0,1}
        那么有以下状态转移:
            (1)不选i + 1:
                dp[i + 1][0] += dp[i][0]
                dp[i + 1][1] += dp[i][1]
            (2)选i + 1, 且i + 1为奇数:
                dp[i + 1][1] += dp[i][0]
            (3)选i + 1, 且i + 1为偶数:
                dp[i + 1][0] += dp[i][1]
        这样, 我们就得到了O(S)解决条件(1)(2)的方法
        如何进行优化呢? 我们发现转移方程都是线性的重复转移, 因此考虑矩阵快速幂
        这里的问题在于: i + 1的不同奇偶性会导致不同的转移方法, 如何进行归一呢?
        我们可以利用trick: 把dp定义更改为 最后一次选的数与(i + s)奇偶性相同
        于是转移方程变为:
            (1)不选i + 1:
                dp[i + 1][0] += dp[i][1]
                dp[i + 1][1] += dp[i][0]
            (2)选i + 1, 且i + 1为奇数:
                dp[i + 1][1] += dp[i][0]
            (3)选i + 1, 且i + 1为偶数:
                dp[i + 1][1] += dp[i][0]
            这时我们惊奇地发现, (2)(3)都变成了相同的转移方程
        因此就可以应用矩阵快速幂来优化了, 在O(logS)时间内便可完成转移
        注: 从转移方程我们也可以看出, 方案数其实就是Fibonacci数列
        那么考虑条件(3)之后如何进行转移呢?
        此时问题稍有变化, 变成了:
            从{0,1,...,S}\{a[1],a[2],...,a[n]}中选任意个数, 并满足0和S必选
            且选出的数字升序排列后相邻两项一奇一偶
        此时我们可以在这N个点手动转移, 转移时只能用方程(1)转移
        其他点仍然使用矩阵快速幂进行转移
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

using Matrix = array<array<int,2>,2>;
using Vector = array<int,2>;

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c{};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                add(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return c;
}

Vector operator * (const Matrix &a, const Vector &b) {
    Vector c{};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            add(c[i], 1LL * a[i][j] * b[j] % MOD);
        }
    }
    return c;
}

Matrix mat{1, 1, 1, 0};

Matrix fast_pow(Matrix a, ll b) {
    Matrix res{1, 0, 0, 1};
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    int n;
    ll S;
    cin >> n >> S;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a.push_back(S);
    Vector f{1, 0};
    for(int i = 0; i <= n; i++) {
        ll L = a[i], R = a[i + 1];
        Matrix to = fast_pow(mat, R - L - 1);
        f = to * f;
        if(i != n) {
            swap(f[0], f[1]);
        }
    }
    cout << f[0] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
