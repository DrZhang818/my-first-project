#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1994/C
/*
    DP
    题意:
        给定一个长度为N的数组和一个阈值x, 定义子数组a[l] ~ a[r]的权值为:
        从a[l]依次累加到a[r], 如果某个时刻总和大于x, 则立刻归零, 最后得到的总和即a[l:r]的权值
        求有多少个子数组的权值不为0
        范围: N∈[1,2e5], x∈[1,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        我们考虑容斥, 维护dp[i] := 以i结尾的权值为0的的子数组个数
        以i结尾的子数组共计有i个, 我们思考如何得到权值不为0的子数组个数
        我们求以i为结尾的后缀和, 显然权值不为0的情况下, 只能是这些 < x的后缀和中的一种
        我们以此做划分, 求出得到每种后缀和的方案数
        想要得到后缀[j, i]
        一种方案是直接取[j, i], 方案数为1
        另一种方案是取以j - 1为结尾的权值为0的子数组后面拼接上[j, i], 方案数为dp[j - 1]
        我们可以用双指针求出最小的满足S[i] - S[j - 1] <= x的下标j, 此时[j, i]是满足 <= x的最大后缀和
        则方案数为∑(dp[o] + 1), o∈[j - 1, i - 1]
        这是以i结尾的权值不为0的子数组数量
        则dp[i] = i - ∑(dp[o] + 1)
        最终答案为∑(i - dp[i])
*/
void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<int> dp(n + 1);
    int l = 0, r = 0;
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        while(pre[i] - pre[l] > x) {
            sum -= dp[l] + 1;
            l++;
        }
        if(r < l) {
            r = l;
            sum = 0;
        }
        while(r < i) {
            sum += dp[r] + 1;
            r++;
        }
        dp[i] = i - sum;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += i - dp[i];
    }
    cout << ans << "\n";
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
