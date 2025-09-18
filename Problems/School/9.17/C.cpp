#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc231/tasks/abc231_e
/*
    DP || 贪心
    题意:
        有N种不同面值的硬币A[i], 满足1 = A[1] < A[2] < ... < A[N], 且A[i + 1]是A[i]的倍数
        你需要购买价格为X的物品, 请你求出 支付 + 找零 最少需要多少枚硬币
        范围: N∈[1,60], A[i]∈[1,1e18], A[1] = 1, X∈[1,1e18]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心||网络流, 常用优化手段为: 二分、前缀和、双指针、数据结构
        注: 赛时做本题时, 严重陷入贪心陷阱无法自拔, 这启示我们在做决策类题目时一定要慎用贪心
        首先思考easy版本: 不考虑找零的情况, 即支付恰好为X, 如何求解?
        这本是一个完全背包问题, 但本题的数据量显然不允许完全背包求解, 应该怎么做呢?
        观察题目性质: A[i + 1]是A[i]的倍数, 这意味着A[i + 1]应该尽可能地多取, 否则少取的部分还需要前面来填充
        所得到的代价必然大于选择A[i + 1]填充
        于是便有了贪心的做法: 从大到小考虑A[i], 每个A[i]能取多少就取多少, 即当前的 X / A[i]
        取完后, X 更新为 X % A[i]
        接下来考虑引入找零情况
        此时问题就有些复杂了, 但好在easy版本给我们提供了一种策略, 我们尝试能否在原策略上稍作修改得到新策略
        我们仍然从大到小考虑, 设当前在考虑A[i], 要组成的值为 X 
        原策略告诉我们, 当前要取 T = floor(X / A[i]) 个
        (1)在考虑找零后, 能否取小于 T 个A[i]呢?
        显然不行, 这会导致接下来还要从A[0] ~ A[i - 1]中选一些数来补充少取的部分, 仍然是劣的
        (2)那么, 能否取 T + 1 个A[i]呢?
        这是有可能的, 取完后的任务就转化成: 从A[0] ~ A[i - 1]中选一些数组成 (T + 1) * A[i] - X
        结合例子来体会: 
            例如用[1, 10, 100]来组成 187, 当前考虑 100 
            原本我们会取 1 个100, 任务转化成从[1, 10]中组成 87 
            现在我们考虑取 2 个100, 任务就变成从[1, 10]中组成 13
            显然在本例中取 2 个100的情况更优
        (3)能否取 >= T + 2个A[i]呢?
        这是不可能的, 因为取T + 1个的时候就已经超过 X 了, 再多取相当于平白无故地多了些需要找零的钱
        综合几种情况, 我们其实能得到以下性质:
        设dp[i][S] := 考虑前i种硬币, 组成S的最小个数
        令 x = a[i], 则有:
            dp[i - 1][S] > dp[i - 1][S - x] > ... > dp[i - 1][S - T * x], 其中S - T * x >= 0
        因此, 在模x同余类中, 取dp[i - 1][S - T * x], 即最接近S的非负整数是最优的
        而取T和T+1正好对应两组不同的模x同余类, 分别求出两组解后取min即可
        更精确地, 我们可以按 floor(X / A[i]) 和 ceil(X / A[i]) 分组
        状态转移就非常简单了:
            dp[i][S] = min(dp[i - 1][S - T * x] + T, dp[i - 1][(T + 1) * x - S] + T + 1)
        由于S非常大, 但实际能达到的状态很少, 因此考虑用map存储dp状态
        如何证明能到达的状态很小呢? 这就需要用到关键性质: A[i + 1] 是 A[i]的倍数
        我们自顶向下考虑, 设当前状态为(i, S), x = A[i]
        则我们会调用(i - 1, S % x)和(i - 1, x - S % x)
        我们令 u = S % x, v = x - S % x
        分别研究(i - 1, u)和(i - 1, v)接下来会如何调用
        (i - 1, u)会调用(i - 2, u % A[i - 1]) 和 (i - 2, A[i - 1] - u % A[i - 1])
        (i - 1, v)会调用(i - 2, v % A[i - 1]) 和 (i - 2, A[i - 1] - v % A[i - 1])
        代入v = A[i] - u
        v % A[i - 1] = (A[i] - u) % A[i - 1] = (-u) % A[i - 1] = A[i - 1] - u % A[i - 1]
        A[i - 1] - v % A[i - 1] = u % A[i - 1]
        惊奇地发现:
            (i - 1, u)和(i - 1, v)的调用是完全相同的, 也就是我们的递归树被严格限制了每层只有2个状态
        如果采用
            floor, ceil写法, 则每层只有 1 or 2个状态
        因此总状态数 <= 2N
        时间复杂度 O(N)
*/

void solve() {
    int n;
    ll x;
    cin >> n >> x;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    map<pair<int,ll>, ll> dp;
    auto dfs = [&](auto &&self, int pos, ll S) -> ll {
        if(pos == 1) {
            return S;
        }
        pair<int,ll> cur = {pos, S};
        if(dp.contains(cur)) {
            return dp[cur];
        }
        ll t1 = S / a[pos], t2 = (S + a[pos] - 1) / a[pos];
        ll x = t1 + self(self, pos - 1, S - t1 * a[pos]);
        ll y = t2 + self(self, pos - 1, t2 * a[pos] - S);
        return dp[cur] = min(x, y);
    };
    cout << dfs(dfs, n, x) << "\n";
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
