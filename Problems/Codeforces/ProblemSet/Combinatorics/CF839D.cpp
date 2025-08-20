#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 1000000;

//https://codeforces.com/contest/839/problem/D
/*
    组合数学 || 数论
    题意:
        给定一个长度为N的数组, 定义一个长度为k的子序列S的权值为f(S) = k * gcd(S), gcd(S)表示S中
        所有元素的最大公约数
        现在你需要求出所有gcd(S) ≠ 1的子序列S的权值之和, 即∑f(S), S满足gcd(S) ≠ 1
        范围: N∈[1,2e5], a[i]∈[1,1e6]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力做法, 枚举所有子集并计算权值, 时间复杂度为O(2^n * n * logM)
        显然, 瓶颈在于枚举子集, 我们要在不逐一枚举的情况下算出答案, 于是考虑贡献法
        我们从f(S)的结构出发: f(S) = k * gcd(S), 是个乘积的形式
        因此我们有两种贡献法路线:
        (1)枚举长度k, 求出∑gcd(S)
        (2)枚举gcd(S), 求出∑k
        路线(1)显然是不好做的, 因为枚举的长度k无法带来有用的信息, 求∑gcd(S)仍然是hard的
        路线(2)就有说法了, 因为a[i] <= 1e6, 我们可以预处理出每个数的因数, 这样我们在枚举
        gcd(S) = x时, 就能知道"哪些集合的gcd可能是x", 这些集合中的每个元素必须都含有因子x
        然而这还不够, 因为我们要求的是"恰好为x", 现在只知道gcd一定是x的倍数, 却不知道哪些是恰好为x的
        于是我们考虑容斥原理:
        我们发现, 对于足够大的x, 即满足2 * x > mx的x来说, 我们得到的是准确值
        那么我们就可以倒序dp, 枚举到x时, 我们能够算出2x, 3x, ...的∑k, 那么就能容斥掉这些, 从而
        得到恰好为x的∑k
        显然这是调和级数枚举, 时间上是允许的
        接下来的问题就是, 对于每个x, 如何求出对应的∑k
        由于上面的容斥帮我们解决了一大难点, 我们不要求选出的集合gcd为x, 只要求每个元素必须包含
        因子x
        那么我们就可以算一下有多少个数包含因子x, 不妨设为n
        这n个数的所有组合都是符合条件的
        即 ∑ k * C(n, k), k∈[1,n]
        然而n <= 2e5, 我们并不能暴力地计算这个数
        经过代数推导, 我们可以得出这个式子的结果为 n * 2^{n - 1}
        这样就可以在O(n)的时间内递推预处理 F(n) = ∑ k * C(n, k)
*/
vector<int> fac[N + 1];
int sum[200001];
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
}
void chmax(int &a, int b) {
    if(a < b) {
        a = b;
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(N + 1);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        chmax(mx, x);
        for(int j : fac[x]) {
            cnt[j]++;
        }
    }
    int ans = 0;
    vector<int> dp(mx + 1);
    for(int i = mx; i >= 2; i--) {
        dp[i] = sum[cnt[i]];
        for(int j = i * 2; j <= mx; j += i) {
            add(dp[i], MOD - dp[j]);
        }
    }
    for(int d = 2; d <= mx; d++) {
        add(ans, 1LL * d * dp[d] % MOD);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(N);
    for(int i = 2; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }
    int cur = 1;
    for(int i = 1; i <= 200000; i++) {
        sum[i] = 1LL * i * cur % MOD;
        cur = 2LL * cur % MOD;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
