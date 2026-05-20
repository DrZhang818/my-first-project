## 1. 题目深度解构

题目定义 $f(n,k)$：满足
$$
0 \le a,b < n
$$
且
$$
k(a+b)\equiv ab \pmod n
$$
的有序整数对 $(a,b)$ 数量。

要求计算：
$$
\sum_{k=0}^{m} f(n,k)
$$
其中：
$$
1\le n\le 10^{14},\quad 0\le m<n
$$
模数为 $998244353$。

这是一道数论计数题。核心不是枚举 $a,b,k$，而是把原同余式转化成关于因子的计数公式。

------

## 2. 思维路径推导

### 第一重观察：把式子配成乘积

原式是：
$$
k(a+b)\equiv ab \pmod n
$$
移项：
$$
ab-ka-kb\equiv 0 \pmod n
$$
看到 $ab-ka-kb$，最自然的动作是补上 $k^2$：
$$
ab-ka-kb+k^2\equiv k^2 \pmod n
$$
即：
$$
(a-k)(b-k)\equiv k^2 \pmod n
$$
由于 $a\mapsto a-k$、$b\mapsto b-k$ 在模 $n$ 意义下都是双射，所以问题等价于：
$$
xy\equiv k^2 \pmod n
$$
其中 $x,y$ 都在模 $n$ 的剩余类中。

所以：
$$
f(n,k)=\#\{(x,y): xy\equiv k^2 \pmod n\}
$$

------

### 第二重观察：固定 $x$，转成线性同余

对于固定的 $x$，考虑：
$$
xy\equiv k^2 \pmod n
$$
设：
$$
d=\gcd(x,n)
$$
线性同余 $xy\equiv k^2\pmod n$ 有解当且仅当：
$$
d\mid k^2
$$
并且有解时，解的数量正好是 $d$。

接下来按 $d=\gcd(x,n)$ 分组。

满足 $\gcd(x,n)=d$ 的 $x$ 数量为：
$$
\varphi\left(\frac nd\right)
$$
因此：
$$
f(n,k)=\sum_{\substack{d\mid n\\ d\mid k^2}} d\varphi\left(\frac nd\right)
$$
这一步是本题的核心数论降维：二维变量 $(x,y)$ 被压成了因子 $d$。

------

### 第三重观察：交换求和顺序

要求：
$$
\sum_{k=0}^{m} f(n,k)
$$
代入公式：
$$
\sum_{k=0}^{m}\sum_{\substack{d\mid n\\ d\mid k^2}} d\varphi\left(\frac nd\right)
$$
交换求和：
$$
\sum_{d\mid n} d\varphi\left(\frac nd\right)\cdot 
\#\{0\le k\le m: d\mid k^2\}
$$
现在只剩一个问题：

给定 $d$，有多少个 $k$ 满足 $d\mid k^2$。

设：
$$
d=\prod p_i^{e_i}
$$
则：
$$
d\mid k^2
$$
等价于：
$$
v_{p_i}(k^2)\ge e_i
$$
也就是：
$$
v_{p_i}(k)\ge \left\lceil\frac{e_i}{2}\right\rceil
$$
所以 $k$ 必须是下面这个数的倍数：
$$
g(d)=\prod p_i^{\lceil e_i/2\rceil}
$$
因此：
$$
\#\{0\le k\le m: d\mid k^2\}
=
\left\lfloor \frac{m}{g(d)}\right\rfloor+1
$$
注意 $k=0$ 也要计入，所以是 $+1$。

最终公式：
$$
\boxed{
\sum_{d\mid n}
d\varphi\left(\frac nd\right)
\left(
\left\lfloor \frac{m}{g(d)}\right\rfloor+1
\right)
}
$$
其中：
$$
g(d)=\prod_{p^e\parallel d}p^{\lceil e/2\rceil}
$$

------

## 3. Trick 与陷阱

本题有三个关键 Trick。

第一，配方：
$$
ab-k(a+b)\Rightarrow (a-k)(b-k)
$$
这是最重要的入口。

第二，线性同余计数：
$$
xy\equiv c \pmod n
$$
固定 $x$，有解当且仅当：
$$
\gcd(x,n)\mid c
$$
且解数为 $\gcd(x,n)$。

第三，平方整除转倍数：
$$
d\mid k^2
$$
不等价于 $d\mid k$，而是等价于：
$$
\prod p^{\lceil e/2\rceil}\mid k
$$
易错点：

1. $k=0$ 必须算进去。
2. $\gcd(0,n)=n$，但分组公式仍然成立，因为 $\varphi(1)=1$。
3. $n\le 10^{14}$，乘法必须用 `long long`，贡献取模后再乘。
4. 不能枚举 $k$，只能枚举 $n$ 的因子。
5. $n=1,m=0$ 时答案是 `1`。

------

## 4. 代码实现（C++23，jiangly 风格）

```
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

constexpr int P = 998244353;

vector<int> primes;

void sieve(int n) {
    vector<char> vis(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            primes.push_back(i);
            if (1LL * i * i <= n) {
                for (i64 j = 1LL * i * i; j <= n; j += i) {
                    vis[j] = 1;
                }
            }
        }
    }
}

vector<pair<i64, int>> factor(i64 n) {
    vector<pair<i64, int>> f;
    for (int p : primes) {
        if (1LL * p * p > n) {
            break;
        }
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            }
            f.push_back({p, e});
        }
    }
    if (n > 1) {
        f.push_back({n, 1});
    }
    return f;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    cin >> T;

    vector<pair<i64, i64>> qry(T);
    i64 mx = 1;

    for (auto &[n, m] : qry) {
        cin >> n >> m;
        mx = max(mx, n);
    }

    int lim = sqrtl(mx) + 2;
    sieve(lim);

    for (auto [n, m] : qry) {
        auto fac = factor(n);

        int s = fac.size();

        vector<vector<i64>> pw(s);
        vector<vector<int>> pm(s), phi(s);

        for (int i = 0; i < s; i++) {
            auto [p, e] = fac[i];

            pw[i].assign(e + 1, 1);
            pm[i].assign(e + 1, 1);
            phi[i].assign(e + 1, 1);

            int q = p % P;

            for (int j = 1; j <= e; j++) {
                pw[i][j] = pw[i][j - 1] * p;
                pm[i][j] = 1LL * pm[i][j - 1] * q % P;
            }

            phi[i][0] = 1;
            for (int j = 1; j <= e; j++) {
                phi[i][j] = 1LL * pm[i][j - 1] * ((p - 1) % P) % P;
            }
        }

        i64 ans = 0;

        auto dfs = [&](auto &&self, int i, i64 g, int d, int ph) -> void {
            if (i == s) {
                i64 cnt = m / g + 1;
                ans = (ans + 1LL * d * ph % P * (cnt % P)) % P;
                return;
            }

            auto [p, E] = fac[i];

            for (int e = 0; e <= E; e++) {
                i64 ng = g * pw[i][(e + 1) / 2];
                int nd = 1LL * d * pm[i][e] % P;
                int np = 1LL * ph * phi[i][E - e] % P;
                self(self, i + 1, ng, nd, np);
            }
        };

        dfs(dfs, 0, 1, 1, 1);

        cout << ans << '\n';
    }

    return 0;
}
```

------

## 5. 复杂度分析

设 $\tau(n)$ 是 $n$ 的因子个数。

每个测试用例需要枚举 $n$ 的所有因子，因此主计算复杂度为：
$$
O(\tau(n))
$$
分解质因数使用预处理质数试除。由于题目保证最多 10 个测试点满足 $n>10^8$，整体可以通过。

空间复杂度：
$$
O(\omega(n))
$$
其中 $\omega(n)$ 是不同质因子的数量。

------

## 6. 总结与启示

预估难度：Codeforces 2300 左右。

核心启示：

> 看到 $ab-k(a+b)$ 这种“乘积 + 一次项”结构，要优先尝试配成 $(a-k)(b-k)$，然后用线性同余的 gcd 解数公式降维。

同类训练方向：

1. 线性同余计数：固定一个变量，把二维同余变成一元线性同余。
2. 因子贡献法：按 $\gcd(x,n)$ 分组。
3. p-adic 指数分析：把 $d\mid k^2$ 转成 $k$ 必须被某个数整除。