#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://codeforces.com/contest/2125/problem/D
/*
    DP || 概率论
    题意:
        在一维数轴上有M个点, 分别位于坐标1,2,...,M, 给定N条线段(l,r,p,q), 该线段覆盖[l,r]内的点,
        且存在的概率为p/q
        你的任务是计算每个点恰好被一个线段覆盖的概率, 对998244353取模       
        范围: N,M∈[1,2e5], 1 <= p < q < 998244353
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先分析题目, 发现N和M都不大, 因此我们考虑枚举其中一个量, 看看能否可以使用dp
        如果我们枚举线段, 会发现很难设计出与最终问题有关的状态
        考虑枚举点, 定义dp[i] := 考虑前i个点, 每个点恰好被一个线段覆盖的概率
        此时, 枚举最后一个点被哪条线段覆盖, 这可以用建图的方式优化枚举, 避免O(N)的枚举时间
        根据加法原理, 总概率应该为被各条线段覆盖的概率之和
        我们设当前第i个点被第j个线段覆盖, 参数为l,r,p,q
        那么这条线段应该满足r = i
        由当前线段来覆盖点i, 则状态转移方程为:
        dp[i] += dp[l - 1] * [l,r]的所有线段中只选第j条线段的概率
        于是问题变成如何求出[l,r]中只选第j条线段的概率
        这件事可以进一步转化为: 
            [l,r]的所有线段都不选的概率 * ¬第j条线段不选的概率 * 选第j条线段的概率
        因此我们可以用一个pre数组, pre[i] := 不选[1,i]的所有线段的概率
        [l,r]所有线段都不选的概率为: pre[r] * (pre[l-1])^{-1}
        ¬第j条不选的概率为: (1 - p/q)^{-1}
        选第j条线段的概率为: p/q
        这样, 我们就完成了这道题的状态转移
*/
struct node {
    int l;
    ll p;
};
ll fast_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<node>> adj(m + 1);
    vector<ll> pre(m + 1, 1);
    for(int i = 1; i <= n; i++) {
        int l, r;
        ll p, q;
        cin >> l >> r >> p >> q;
        ll cur = (q - p) * fast_pow(q, MOD - 2) % MOD;
        adj[r].push_back({l, cur});
    }
    vector<ll> dp(m + 1);
    dp[0] = 1;
    ll cur = 1;
    for(int i = 1; i <= m; i++) {
        for(auto [l, p] : adj[i]) {
            cur = cur * p % MOD;
        }
        pre[i] = cur;
        for(auto [l, p] : adj[i]) {
            dp[i] += dp[l - 1] * cur % MOD * fast_pow(p, MOD - 2) % MOD * (1 - p + MOD) % MOD * fast_pow(pre[l - 1], MOD - 2) % MOD;
            dp[i] %= MOD;
        }
    }
    cout << dp[m] << "\n";
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
