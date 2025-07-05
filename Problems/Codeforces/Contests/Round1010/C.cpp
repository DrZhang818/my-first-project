#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
constexpr int inf = 1000000000;

//https://codeforces.com/contest/2082/problem/C
/*
    期望DP
    题意:
        给定一个长度为N的二进制字符串表示一个整数x, 为了让x变成1, 你会采取以下两种操作
        op1: 将x替换为x // 2
        op2: 将x替换为(x + 1) // 2
        每次操作你都会等概率(50%)随机选择op1或op2, 各个操作之间独立
        要求计算出使得x变成1的操作次数的期望值, 对1000000007取模
        范围: N∈[1,1e5]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先介绍一个引理: 设一个数进行了K次操作, 其中n次为上取整, m次为下取整
        则无论n,m的次数如何分布, 无论操作顺序如何, 所得到的结果相差不超过1
        对于期望问题, 我们可以用期望DP来思考问题
        定义E(x) := 将x变成1的期望次数
        则由全期望公式, E[x] = 1 + (1/2)*E[x//2] + (1/2)*E[(x+1)//2]
        但由于x的值域过大, 我们不可能把x作为状态, 观察上面的式子
        设x是字符串前i位所表示的十进制数
        那么x // 2就是前i-1位所表示的十进制数!
        问题在于(x+1)//2不太好处理, 但由上面的引理可知, (x+1)//2∈[x//2,x//2+1]
        因此我们有了以下巧妙的dp定义方式:
        g(S) := 将字符串S变成1的期望次数
        h(S) := 将字符串S + 1变成1的期望次数
        G[i] := 考虑字符串前i位表示的数变成1的期望次数
        H[i] := 考虑字符串前i位表示的数 + 1 变成1的期望次数
        下面思考转移方程:
        这里为了方便表示, 我们把S写成Ab的形式, A为S去除最后一位得到的前缀, b为0/1
        (1)如果x是偶数, 即s[i] = '0'的情况
        此时g(A0) = 1 + g(A), h(A0) = g(A1) = 1 + (1/2)*g(A) + (1/2)*h(A)
        G[i] = 1 + G[i - 1]
        H[i] = 1 + (1/2)*G[i-1] + (1/2)*H[i-1]
        (2)如果x是奇数, 即s[i] = '1'的情况
        此时g(A1) = 1 + (1/2)*g(A) + (1/2)*h(A)
            h(A1) = g(A1 + 1) = g((A + 1)0) = 1 + g(A + 1) = 1 + h(A)
        G[i] = 1 + (1/2)*G[i - 1] + (1/2)*H[i - 1]
        H[i] = 1 + H[i - 1] 
*/
constexpr int MOD = 1000000007;
ll pow_mod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
inline ll inv(ll x) { return pow_mod(x, MOD - 2); } 
//Gemini做法: 期望DP
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    ll inv2 = inv(2);
    vector<ll> G(n + 1), H(n + 1);
    G[1] = 0, H[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(s[i - 1] == '0') {
            G[i] = (1 + G[i - 1]) % MOD;
            H[i] = (1 + G[i - 1] * inv2 % MOD + H[i - 1] * inv2 % MOD) % MOD;
        } else {
            G[i] = (1 + G[i - 1] * inv2 % MOD + H[i - 1] * inv2 % MOD) % MOD;
            H[i] = (1 + H[i - 1]) % MOD;
        }
    }
    cout << G[n] << "\n";
}

//自己的做法
void solve1() {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    s = "#" + s;
    ll inv2 = inv(2);
    vector dp(n + 1, vector<ll>(2));
    dp[0][0] = 1, dp[0][1] = 0;
    for(int i = 1; i < n; i++) {
        if(s[i] == '0') {
            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] * inv2) % MOD;
            dp[i][1] = dp[i - 1][1] * inv2 % MOD;
        } else {
            dp[i][0] = dp[i - 1][0] * inv2 % MOD;
            dp[i][1] = (dp[i - 1][1] + dp[i - 1][0] * inv2 % MOD) % MOD;
        }
    }
    dp[n][1] = dp[n - 1][1];
    ll ans = (n * dp[n][1] % MOD + (n - 1) * dp[n - 1][0] % MOD) % MOD;
    cout << ans << "\n"; 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
