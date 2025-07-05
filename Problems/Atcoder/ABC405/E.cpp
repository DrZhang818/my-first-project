#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc405/tasks/abc405_e
/*
    组合数学 || 拓扑排序
    题意:
        给定四种类型水果(ABCD)的数量, 要求把所有的水果从左到右排成一行, 并满足以下要求:
        (1)所有的类型A水果都位于类型C水果的左边
        (2)所有的类型A水果都位于类型D水果的左边
        (3)所有的类型B水果都位于类型D水果的左边
        求符合要求的排列方式的数量, 结果对998244353取模
        范围: A,B,C,D∈[1,1e6]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力做法, 逐一检查(A+B+C+D)!/A!/B!/C!/D!种状态, 时间复杂度极其大
        瓶颈在于状态量爆炸, 因此我们的目标就是对状态进行划分/剪枝, 避免无效状态的访问
        观察题目性质, 我们发现四种水果间形成拓扑序关系, 由于A的出度最多, 我们从A开始考虑
        我们考虑最后一个A的位置i, 这个点是很特殊的, 因为在这一点之前不允许C和D的出现
        因此我们利用水果A可以把这N个位置划分成两段, 第一段是由a个A类型水果和i-a个B类型水果组成
        下面考虑第二段: 同样地按照最后一个B地位置j进行划分
        在(i, j]之间只允许B和C同时出现
        在(j, N]之间只允许C和D同时出现
        这样我们就成功地把这N个位置划分成了三段: [1,i]∪(i,j]∪(j,N]  (注意j可能小于i, 此时第二段为空)
        然后我们会发现, 在第二段和第三段都允许C出现, 因此C的限制最少, 那么就考虑C的方案数
        当A和C的位置确定之后, B和D的位置也确定了, 因为B一定在D的左边
        问题就变成了求解放置A和C的方案数
        A的方案数就是∑C[A-1+i][A-1] i∈[0,B]
        在A固定之后, C的方案数为C[N-A-i][C]
        因此答案为∑C[A-1-i][A-1] * C[N-A-i][C]
*/
const int MOD = 998244353;
ll fac[4000005];
ll pow_mod(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll inv_fac(ll x) {
    return pow_mod(fac[x], MOD - 2);
}
ll C(ll a, ll b) {
    return fac[a] * inv_fac(b) % MOD * inv_fac(a - b) % MOD;
}
void solve() {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    ll ans = 0, n = a + b + c + d;
    for(int i = 0; i <= b; i++) {
        ans = (ans + C(a - 1 + i, a - 1) * C(n - a - i, c) % MOD) % MOD;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= 4000000; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
