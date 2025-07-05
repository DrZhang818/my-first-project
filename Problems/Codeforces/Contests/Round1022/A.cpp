#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2108/problem/A
/*
    数学
    题意:
        对于一个长度为N的排列p, 定义f(p) := ∑|pi - i| i∈[1,N]
        给定一个数字N, 求出f(p)有多少种可能值
        范围: N∈[1,500]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察题目性质, 可以发现f(p)的值只能为偶数, 因为交换排列中两个数奇偶性不变
        证: |x - i| + |y - j| ≡ |y - i| + |x - j| (mod 2)
        引理: |k| ≡ k (mod 2)
        由引理, 我们可以直接去掉绝对值, 因此原命题成立
        而当排列为1~N顺序排列时, Σ|pi-i| = 0, 可知f(p)的值一定是偶数
        此时我们进一步发现, 只要找到最小值和最大值, 那么中间的偶数一定都可以取到
        只需证明任何排列都可以通过步进为0/-2到达初始排列1,2,...,n
        这样中间的每个偶数都可以在过程中取到
        我们考虑让最大的"未归位"的数字向右逐步归位, 这样每步就贡献了-1的步进
        而由于上述讨论的奇偶性不变, 总贡献必然是偶数
        再由邻位交换可知, i与j相差1, 则|x-i|与|x-j|的差值只能为-1或1
        因此交换后的贡献为0/-2, 这意味着按照这种策略, 最大值对应的排列调整为原始排列
        的过程中, 一定可以取得中间值
        下面考虑最大值是多少:
        显然逆序排列就是最大的, 即每次将最大的与最小的匹配, 最小的与最大的匹配
        这一点很容易用贪心证明, 不再论证
*/
void solve() {
    int n;
    cin >> n;
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += abs(n - i + 1 - i);
    }
    ans = ans / 2 + 1;
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
