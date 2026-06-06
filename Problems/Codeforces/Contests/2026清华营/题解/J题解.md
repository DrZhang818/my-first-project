## 1. 题目深度解构

### 题意重述

给定整数 $n, m$。从 $0,1,\dots,m-1$ 中选出 $n$ 个互不相同的数并排成一个序列。

对一个序列 $a_1,\dots,a_n$，定义它的强度为所有前缀的 mex 之和：
$$
f(a_1,\dots,a_n)=\sum_{i=1}^{n}\operatorname{mex}(a_1,\dots,a_i)
$$
要求计算所有长度为 $n$ 的无重复序列的强度总和，模 $10^9+7$。

------

### 约束分析

$$
1 \le n \le 10^6,\qquad n \le m \le 10^9
$$

关键点：

- 序列总数是排列数 $(m)_n$，完全不能枚举。
- $m$ 高达 $10^9$，不能预处理到 $m$。
- $n$ 是 $10^6$，允许 $O(n)$ 或 $O(n \log MOD)$，但 1 秒下更理想是 $O(n)$。
- 所有元素互不相同，这是计数公式能化简的核心。

### 类型判定

这是一道 **组合计数 + mex 指标化 + 前缀贡献拆分** 的思维题。

核心技巧：

- 线性拆贡献；
- 将 mex 转成若干个“是否包含 $0,1,\dots,k-1$”的指示器；
- 使用 Hockey-stick 组合恒等式；
- 最后用前缀积 / 后缀积避免除法。

------

## 2. 思维路径推导

### 从暴力开始

最朴素的想法是枚举所有合法序列。

合法序列数是：
$$
m(m-1)(m-2)\cdots(m-n+1)
$$
当 $n=10^6$，$m=10^9$ 时完全不可行。

于是我们不枚举序列，而是把总和按前缀长度拆开。

设第 $i$ 个前缀的 mex 对总答案的贡献为 $C_i$，那么答案是：
$$
\sum_{i=1}^{n} C_i
$$
固定前缀长度 $i$。

如果已经确定了一个长度为 $i$ 的有序无重复前缀，那么后面还有 $n-i$ 个位置，需要从剩余 $m-i$ 个数里有序选择。

补全方案数为：
$$
(m-i)(m-i-1)\cdots(m-n+1)
$$
也就是：
$$
(m-i)_{n-i}
$$
这个数量只和 $i$ 有关，和具体前缀内容无关。

所以问题变成：求所有长度为 $i$ 的有序无重复前缀的 mex 总和。

------

### 关键观察：mex 不好直接算，但可以拆成指示器

对于一个前缀集合 $S$，如果：
$$
\operatorname{mex}(S)=x
$$
那么说明：
$$
0,1,\dots,x-1
$$
都出现了。

因此：
$$
\operatorname{mex}(S)
=
\sum_{k=1}^{i}
[0,1,\dots,k-1 \text{ 都出现在 } S \text{ 中}]
$$
这一步是整题的 Aha moment。

我们不直接数 mex 等于多少，而是数 mex 至少是多少。

固定 $k$，我们要数长度为 $i$ 的有序无重复前缀，使得 $0,1,\dots,k-1$ 这 $k$ 个数全部出现。

计数方式：

- 这 $k$ 个数必须选；
- 还要从剩下的 $m-k$ 个数中选 $i-k$ 个；
- 最后把这 $i$ 个数任意排列。

所以数量是：
$$
i! \binom{m-k}{i-k}
$$
因此长度为 $i$ 的所有前缀的 mex 总和为：
$$
T_i
=
\sum_{k=1}^{i} i!\binom{m-k}{i-k}
$$
把 $j=i-k$，则：
$$
\sum_{k=1}^{i}\binom{m-k}{i-k}
=
\sum_{j=0}^{i-1}\binom{m-i+j}{j}
=
\binom{m}{i-1}
$$
所以：
$$
T_i = i!\binom{m}{i-1}
$$
继续化简：
$$
i!\binom{m}{i-1}
=
i \cdot m(m-1)\cdots(m-i+2)
$$
也就是：
$$
T_i = i \prod_{j=1}^{i-1}(m-j+1)
$$
第 $i$ 个前缀后面的补全数量是：
$$
\prod_{j=i+1}^{n}(m-j+1)
$$
于是：
$$
C_i
=
i
\left(\prod_{j=1}^{i-1}(m-j+1)\right)
\left(\prod_{j=i+1}^{n}(m-j+1)\right)
$$
令：
$$
b_j=m-j+1
$$
那么：
$$
C_i = i \prod_{j\ne i} b_j
$$
最终答案就是：
$$
\sum_{i=1}^{n} i \prod_{j\ne i}(m-j+1)
$$
这个形式非常适合用前缀积和后缀积 $O(n)$ 计算。

------

## 3. Trick 与陷阱

### Trick 点拨

本题的核心 Trick 是：

> 把 mex 转换成“前若干个非负整数是否全部出现”的指示器之和。

即：
$$
\operatorname{mex}(S)
=
\sum_{k\ge 1} [0,1,\dots,k-1 \subseteq S]
$$
这让 mex 的计数从“精确等于某值”变成了“包含某个固定集合”，后者非常容易组合计数。

另一个关键是 Hockey-stick 恒等式：
$$
\sum_{j=0}^{i-1}\binom{m-i+j}{j}
=
\binom{m}{i-1}
$$

------

### 易错点

1. **不要预处理到 $m$**
    $m\le 10^9$，只能处理长度为 $n$ 的连续乘积。
2. **不要每一项都快速幂求逆**
    虽然可以用除法公式，但 1 秒限制下不够优雅。前缀积 / 后缀积可以完全避免除法。
3. **$n=1$ 的空乘积要处理正确**
    代码中 `pre[0]=1`，后缀初始为 `1`，自然处理。
4. **乘法要用 `long long`**
    模数接近 $10^9$，两个数相乘会爆 `int`。

------

## 4. 代码实现 C++23

```
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

constexpr int P = 1000000007;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    i64 m;
    cin >> n >> m;

    vector<int> pre(n + 1);
    pre[0] = 1;

    for (int i = 1; i <= n; i++) {
        pre[i] = 1LL * pre[i - 1] * ((m - i + 1) % P) % P;
    }

    i64 ans = 0;
    i64 suf = 1;

    for (int i = n; i >= 1; i--) {
        ans = (ans + 1LL * i * pre[i - 1] % P * suf) % P;
        suf = suf * ((m - i + 1) % P) % P;
    }

    cout << ans << "\n";

    return 0;
}
```

复杂度：
$$
O(n)
$$
内存：
$$
O(n)
$$

------

## 5. 总结与启示

### 难度评分

预估 Codeforces Rating：**2200 左右**。

### 核心启示

> 遇到 mex 总和问题时，不要急着按 mex 的具体值分类，优先考虑把 mex 写成“前缀整数集合是否完整出现”的指示器之和。

### 同类习题推荐

1. **Codeforces 1436C - Binary Search**
    排列计数、固定若干位置约束后使用 falling factorial。
2. **AtCoder ABC172 E - NEQ**
    组合计数、排列数、容斥思想。
3. **Codeforces 1744F - MEX vs MED**
    围绕 mex 的集合性质进行结构化计数。