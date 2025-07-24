#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://codeforces.com/contest/2027/problem/D2
/*
    DP || 贪心 || 三指针
    题意:
        给定一个长度为N的数组a和一个长度为M的数组b, 起初k的值为1, 你需要通过以下操作使得数组a变为空
        op1: 如果k < m且a非空, 你可以将k的值增加1, 代价为0
        op2: 移除数组a的一个非空前缀, 满足前缀和不超过b[k], 代价为M - k
        你需要求出最小代价和得到最小代价的方案数, 如果无法使数组a变为空, 输出-1
        范围: N,M∈[1,3e5], N*M∈[1,3e5], a[i],b[i]∈[1,1e9]
    关键思考:
        本题在D1基础上多了计数部分, 我们这里只探讨如何计算方案数
        首先思考什么时候会出现多种方案
        我们利用在D1中利用dp来进行决策, 而dp本身具有最优子结构, 因此我们要统计的是在最后一步决策时
        有多少种选择方案
        在最后一步决策时, 我们要获得dp[i]的值, 那我们的上一步的j必须满足pre[i] - pre[j-1] <= b[k]
        转移方程是dp[i] = dp[j] + m - k
        我们在D1中用了贪心的方式, 求解满足pre[i]-pre[j-1]<=k的最小的j, 我们记为L
        那么接下来的问题就是, 统计有多少个j∈[L,i], 满足dp[j] = dp[L]
        令cnt[i]表示得到dp[i]的方案数
        那么如果dp[L]+m-k == dp[i], 有cnt[i] += ∑cnt[j]
            如果dp[L]+m-k < dp[i], 那么cnt[i] = ∑cnt[j]
        由于dp[]具有单调性, 因此满足dp[j] = dp[L]的j必然是一个连续的段, 这样就可以用双指针维护
        我们梳理一下, 随着i的增大, L增大, R也跟着增大, 用sum变量统计∑dp[L:R]即可
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    int mx = *max_element(a.begin() + 1, a.end());
    if(mx > b[1]) {
        cout << -1 << "\n";
        return;
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<int> dp(n + 1, inf), cnt(n + 1);
    dp[0] = 0;
    cnt[0] = 1;
    for(int k = 1; k <= m; k++) {
        int sum = 0;
        for(int i = 1, L = 0, R = 0; i <= n; i++) {
            while(pre[i] - pre[L] > b[k]) {
                add(sum, MOD - cnt[L]);
                L++;
            }
            if(R < L) {
                R = L;
                sum = 0;
            }
            while(R < i && dp[R] == dp[L]) {
                add(sum, cnt[R]);
                R++;
            }
            if(L < i) {
                int v = dp[L] + m - k;
                if(v < dp[i]) {
                    dp[i] = v;
                    cnt[i] = sum;
                } else if(v == dp[i]) {
                    add(cnt[i], sum);
                }
            }
        }
    }
    cout << dp[n] << " " << cnt[n] << "\n";
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
