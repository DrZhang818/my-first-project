#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc411/tasks/abc411_e
/*
    组合数学 || DP || 建图
    题意:
        有N个6面骰子, 每个面印有一个数字
        同时抛出这N个骰子, 记每个骰子朝上的面的值为A_i, max(A_1,...,A_n)为权值F
        假设每个面朝上的概率相同, 求F的期望
        范围: N∈[1,1e5], A_i∈[1,1e9]
    关键思考:
        本题为计算类题目, 常用思考方式为: 暴力->DP||数学, 常用优化手段为: 双指针、分块、前缀和、数据结构
        首先观察题目性质, 不难想到枚举最大值的暴力做法, 时间复杂度为O(n^3)
        记P_i(x) := 第i个的骰子满足性质x的概率
        则最大值为m的总概率为P(m):
            P_1(m)∧P_2(<=m)∧...∧P_n(<=m) +...+ P_1(<=m)∧...∧P_{n-1}(<=m)∧P_n(m)
        显然有以下优化方法: 
            由于恰好型不方便计算, 我们转化为至少型
            P(m) = P(<=m) - P(<=m-1)
        这样就把时间复杂度优化成了O(n^2)
        同时我们发现, 这里有明显的拓扑关系, P(<=m)可以在P(<=m-1)的基础上计算出来
        具体地, 找到所有含有m的骰子, 算出<=m和<=m-1的次数, 更新P(<=m-1)即可得到P(<=m)
        由于每个骰子最多参与6次更新, 因此建图优化后时间复杂度为O(n)
*/
const int MOD = 998244353;
ll fast_pow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll inv[7];
void solve() {
    int n;
    cin >> n;
    vector<array<int,7>> a(n + 1);
    int mn = -inf;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 6; j++) {
            cin >> a[i][j];
        }
        sort(a[i].begin() + 1, a[i].end());
        mn = max(mn, a[i][1]);
    }
    map<int,vector<int>> mp;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 6; j++) {
            if(a[i][j] <= mn || a[i][j] == a[i][j - 1]) continue;
            mp[a[i][j]].push_back(i);
        }    
    }
    ll p = 1;
    for(int i = 1; i <= n; i++) {
        int cnt = 0;
        for(int j = 1; j <= 6; j++) {
            if(a[i][j] <= mn) {
                cnt++;
            }
        }
        p = p * cnt * inv[6] % MOD;
    }
    ll ans = mn * p % MOD;
    for(auto &[x, vec] : mp) {
        ll np = p;
        for(int j : vec) {
            int c0 = 0, c1 = 0;
            for(int k = 1; k <= 6; k++) {
                if(a[j][k] < x) {
                    c0++;
                }
                if(a[j][k] <= x) {
                    c1++;
                }
            }
            np = np * c1 * inv[c0] % MOD;
        }
        ans = (ans + (np - p + MOD) % MOD * x) % MOD;
        p = np;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 6; i++) {
        inv[i] = fast_pow(i, MOD - 2);
    }
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
