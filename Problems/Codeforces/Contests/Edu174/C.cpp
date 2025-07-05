#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2069/problem/C
/*
    DP
    题意:
        给定一个长度为n的数组, 数组元素范围是1~3, 计算它的合法子序列个数
        一个序列是合法的, 当且仅当它满足以下三条原则
        (1)长度至少为3
        (2)除第一个元素外, 每个元素左边都有一个比它更小的数
        (3)除最后一个元素外, 每个元素右边都有一个比它更大的数
        结果对998244353取模
        范围: n∈[3,2e5], a[i]∈[1,3]
    关键思考:
        本题是计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为:前缀和、数据结构、数学
        本题最明显的性质是: 
        (1)开头必须是1, 结尾必须是3, 其余数字必须是2
        即只有 1[2...2]3这样的序列是合法的
        暴力做法是枚举每个1, 与后面的每个3进行配对, 并维护2的个数
        这样的做法是O(n^2)的, 需要优化
        优化的核心在于, 暴力做法中, 瓶颈是每个3都会被多次访问, 所以我们就尝试能否一次性地
        把每个3的贡献计算出来
        而要做到这一点, 我们就要维护前面的合法"12"对的个数
        而这就是一个很经典的状态机DP问题
        dp[i][1] := 前i个位置, 序列为1的个数
        dp[i][2] := 前i个位置, 序列为1[2...2]的个数
        如果a[i] = 1, 那么dp[i][1] = dp[i - 1][1] + 1, dp[i][2] = dp[i-1][2]
        如果a[i] = 2, 那么dp[i][2] = dp[i - 1][2] * 2 + dp[i - 1][1], dp[i][1] = dp[i-1][1]
        如果a[i] = 3, 那么dp[i][1] = dp[i - 1][1], dp[i][2] = dp[i - 1][2]
        dp[i][2]的转移可以解释为:
            继承: 前面的合法状态后面接上/不接上当前的2
            发展: 前面的1可以直接接上当前的2
        这样遇到3, 我们只需要加上dp[i][2]即可
*/
const int MOD = 998244353;
void solve(){ 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll c1 = 0, pair = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) {
            c1 += 1;
        } else if(a[i] == 2) {
            pair = 2 * pair + c1;
            pair %= MOD;
        } else {
            ans += pair;
            ans %= MOD;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
