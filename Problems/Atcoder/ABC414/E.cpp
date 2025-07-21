#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;
const int inv2 = (MOD + 1) >> 1;

//https://atcoder.jp/contests/abc414/tasks/abc414_e
/*
    数论
    题意:
        给定一个整数N, 你需要找到满足以下条件的三元组(a,b,c)的数量:
        (1)1 <= a,b,c <= N
        (2)a,b,c两两互不相同
        (3)a % b = c
        结果对998244353取模
        范围: N∈[3,1e12]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        由于N非常大, 显然暴力手段是不能使用的
        我们考虑使用数学的方式, 首先对a,b,c的范围进行研究
        由模运算性质可知, c∈[0,b], 而c >= 1, 因此c∈[1,b]
        由于a,b,c两两互不相同, 因此a必须大于b, 而a % b ≠ 0, 因此a∈[b+1,N]∧¬(b整除a)
        因为b = a时一定不满足¬(b整除a), 因此上面的条件可以等价成a∈[b,N]∧¬(b整除a)
        ¬(b整除a)不容易计数, 我们利用容斥来做
        即(N-b+1) - a∈[b,N]∧(b整除a)
        对b进行求和, 则得到以下式子:
        N(N+1)/2 - ∑(N//b), b∈[1,N]
        这是经典的数论分块

        我们还可以考虑第二种方法:
        枚举b和c
        对于每个b对应的每个c∈[1,b-1], 我们计算有多少个a
        不难证明, 方案数是N//b - 1 + [N % b ∈ [1,c]]
        对c求和, 得到:
            ∑(b-1)N//b - ∑1 + ∑(N % b)
        这里重点说明第三项的求法:
        在数论分块的过程中, 在同一个块内, N // b是相同的, 此时N % b呈现等差数列形式
        L对应块内N % b的最大值, R对应块内N % b的最小值
        公差是N // b
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    ll n;
    cin >> n;
    int ans = 1LL * (n % MOD) * ((n + 1) % MOD) % MOD * inv2 % MOD;
    int tot = 0;
    for(ll L = 1, R; L <= n; L = R + 1) {
        R = n / (n / L);
        int div = (n / L) % MOD;
        int len = (R - L + 1) % MOD;
        add(tot, 1LL * div * len % MOD);
    }
    cout << (ans - tot + MOD) % MOD << "\n";
}

// void solve() {
//     ll n;
//     cin >> n;
//     int u, v, w;
//     u = v = w = 0;
//     v = (n - 1) % MOD * ((n - 2) % MOD) % MOD * inv2 % MOD;
//     for(ll L = 2, R; L <= n - 1; L = R + 1) {
//         ll div = n / L;
//         R = n / div;
//         R = min(R, n - 1);
//         add(u, div % MOD * ((L + R - 2) % MOD) % MOD * ((R - L + 1) % MOD) % MOD * inv2 % MOD);
//         ll x = n % L, y = n % R;
//         add(w, (x + y) % MOD * (((x - y) / div + 1) % MOD) % MOD * inv2 % MOD);
//     }
//     cout << (((ll)u - v + w) % MOD + MOD) % MOD << "\n";
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
