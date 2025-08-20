#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 100000007;

//https://www.luogu.com.cn/problem/P1976
/*
    组合数学 || Catalan数
    题意: 
        在圆上有2N个不同的点, 用N条线段把这些点连接起来(每个点恰好连一条线段), 使所有的线段都不相交
        求不同的连接方案数量, 结果对1e8 + 7取模
        范围: N∈[1,2999]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        我们把这2N个点按照顺时针顺序用1~2N进行标定, 显然, 我们只能把奇数点和偶数点进行匹配
        考虑第1个点与2i进行匹配, 则下面的问题就变成了:
        求2~2i-1的合法连接数量
        求2i+1~2N的合法连接数量
        这是标准的Catalan数合法括号序列模型
        计算C(n)即可
*/
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
void solve() {
    int n;
    cin >> n;
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        ans = 1LL * ans * (4 * i - 2) % MOD * inv(i + 1) % MOD;
    } 
    cout << ans << "\n";
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
