## 1. 题目深度解构

### 题意重述

给定一条闭合折线，保安沿折线按固定方向巡逻。每条线段上，保安的视野方向固定为该线段的前进方向，视野是一个半径为 `r`、半角为 `a` 的扇形。

有 `m` 个展品点。要求统计：

对于每个 `k = 0, 1, ..., m`，保安在巡逻路线上的哪些位置能同时看到恰好 `k` 个展品，并输出这些位置的总长度。

线段端点是否能看见不重要，因为端点长度为 `0`，不会影响答案。

### 约束分析

$$
n, m \le 2000
$$

所以：
$$
n \times m \le 4 \times 10^6
$$
这是可以接受的。

每条线段上处理所有展品，如果每个展品能在 `O(1)` 内转化成一个区间，再对区间端点排序扫描，那么复杂度为：
$$
O(nm \log m)
$$
在 3 秒、1024 MB 限制下是合理的。

### 题目类型判定

这是计算几何 + 区间扫描题。

核心不是复杂几何，而是把“移动点的扇形视野”转化成“线段上的可见区间”。

------

## 2. 思维路径推导

### 朴素想法

最暴力的想法是：枚举保安在线段上的很多位置，判断每个位置能看到几个展品。

但保安的位置是连续的，不能离散采样。采样会产生误差，而且无法保证答案精确到 `1e-6`。

所以必须找到每个展品在哪些连续位置可见。

### 关键观察

固定一条巡逻线段，保安的前进方向是固定的。

固定一个展品 `Q`，随着保安在线段上移动，`Q` 是否可见只和保安在线段上的参数位置有关。

更重要的是：

> 对于一条固定线段和一个固定展品，展品可见的位置一定是一个区间。

这是本题的核心 Aha moment。

### 坐标系转化

考虑一条线段：
$$
A \to B
$$
长度为：
$$
L = |B - A|
$$
单位方向向量为：
$$
\vec u = \frac{B - A}{|B - A|}
$$
设保安在线段上的位置为：
$$
P(t) = A + t\vec u,\quad 0 \le t \le L
$$
对于展品点 `Q`，把它放到以 `A` 为原点、以 `u` 为 x 轴的局部坐标系里。

令：
$$
X = (Q - A) \cdot \vec u
$$
表示展品在前进方向上的投影距离。

令：
$$
Y = \vec u \times (Q - A)
$$
表示展品到当前线段所在直线的有向垂直距离。

当保安在 `P(t)` 时，展品相对保安的位置是：
$$
(X - t, Y)
$$
记：
$$
s = X - t
$$
那么 `s` 是展品在保安前方方向上的距离。

展品在扇形内需要同时满足两个条件。

第一，角度条件：
$$
|Y| \le s \tan a
$$
因为扇形半角是 `a`。

第二，距离条件：
$$
s^2 + Y^2 \le r^2
$$
同时，由于 `0 < a < 90^\circ`，角度条件本身会要求 `s >= 0`。

于是：
$$
s \ge \frac{|Y|}{\tan a}
$$
并且：
$$
s \le \sqrt{r^2 - Y^2}
$$
所以只有当：
$$
|Y| \le r
$$
且
$$
\frac{|Y|}{\tan a} \le \sqrt{r^2 - Y^2}
$$
时，展品才可能被看见。

此时：
$$
s \in \left[\frac{|Y|}{\tan a},\ \sqrt{r^2 - Y^2}\right]
$$
又因为：
$$
s = X - t
$$
所以：
$$
t = X - s
$$
因此保安可见该展品的位置区间是：
$$
t \in \left[
X - \sqrt{r^2 - Y^2},\ 
X - \frac{|Y|}{\tan a}
\right]
$$
最后再和当前线段范围 `[0, L]` 取交集即可。

### 问题转化

对于每条线段：

1. 对每个展品算出一个可见区间。
2. 得到最多 `m` 个区间。
3. 在线段上扫描这些区间端点。
4. 某段连续长度内覆盖区间数为 `k`，就把这段长度加到 `ans[k]`。

这就是标准的区间覆盖计数。

------

## 3. Trick 与陷阱

### Trick 点拨

本题的关键 Trick 是局部坐标系。

把展品相对线段起点 `A` 投影到：

- 前进方向；
- 垂直方向；

之后，二维扇形问题就变成了一维参数 `t` 上的区间问题。

另一个 Trick 是扫描线：

区间 `[l, r]` 转化为：

```
(l, +1)
(r, -1)
```

排序后从左到右扫，当前覆盖数就是当前位置能看到的展品数量。

### 易错点

1. 输入的 `a` 是半角，不是整个视野角度。题目说 central angle 是 `2a`。
2. 最后一条线段是：

$$
p_n \to p_1
$$

不要漏掉闭合边。

1. 线段端点不计入巡逻点，但端点长度为 `0`，对总长度没有影响，不需要特殊处理。
2. 要使用 `long double`，最后输出足够多位小数。
3. 如果 `|Y| > r`，展品一定不可见，因为垂直距离已经超过视野半径。
4. 区间必须和 `[0, L]` 取交集。

------

## 4. 代码实现 C++23

```
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using ld = long double;

struct P {
    ld x, y;
};

P operator-(P a, P b) {
    return {a.x - b.x, a.y - b.y};
}

ld dot(P a, P b) {
    return a.x * b.x + a.y * b.y;
}

ld cross(P a, P b) {
    return a.x * b.y - a.y * b.x;
}

void solve() {
    int n, m;
    ld r, a;
    cin >> n >> m >> r >> a;

    vector<P> p(n), q(m);

    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    for (int i = 0; i < m; i++) {
        cin >> q[i].x >> q[i].y;
    }

    const ld pi = acosl(-1.0L);
    ld tg = tanl(a * pi / 180.0L);

    vector<ld> ans(m + 1);

    for (int i = 0; i < n; i++) {
        P A = p[i];
        P B = p[(i + 1) % n];

        P v = B - A;
        ld L = hypotl(v.x, v.y);
        P u = {v.x / L, v.y / L};

        vector<pair<ld, int>> e;
        e.reserve(2 * m);

        for (auto Q : q) {
            P w = Q - A;

            ld X = dot(w, u);
            ld Y = cross(u, w);
            ld ay = fabsl(Y);

            if (ay > r + 1E-12L) {
                continue;
            }

            ld hi2 = r * r - ay * ay;
            if (hi2 < 0) {
                hi2 = 0;
            }

            ld hi = sqrtl(hi2);
            ld lo = ay / tg;

            if (lo > hi + 1E-12L) {
                continue;
            }

            ld l = X - hi;
            ld rr = X - lo;

            l = max<ld>(l, 0);
            rr = min<ld>(rr, L);

            if (l < rr) {
                e.push_back({l, 1});
                e.push_back({rr, -1});
            }
        }

        sort(e.begin(), e.end());

        ld last = 0;
        int cur = 0;

        for (auto [x, d] : e) {
            if (x > last) {
                ans[cur] += x - last;
                last = x;
            }
            cur += d;
        }

        if (last < L) {
            ans[cur] += L - last;
        }
    }

    cout << fixed << setprecision(15);

    for (int i = 0; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    solve();

    return 0;
}
```

复杂度：
$$
O(nm \log m)
$$
空间复杂度：
$$
O(m)
$$

------

## 5. 总结与启示

### 难度评分

预估 Codeforces Rating：
$$
2000 \sim 2200
$$
这题的实现不长，但需要准确完成几何建模。

### 核心启示

连续移动视野问题，不要采样；固定目标后，优先判断“可行位置集合”能否转化为区间。

### 同类习题推荐

1. Codeforces 1000C - Covered Points Count
    练习区间覆盖次数统计。
2. AtCoder ABC221 D - Online games
    练习扫描线统计“恰好覆盖 k 次”的长度。
3. CSES - Point Location Test
    练习点积、叉积和二维几何坐标变换。