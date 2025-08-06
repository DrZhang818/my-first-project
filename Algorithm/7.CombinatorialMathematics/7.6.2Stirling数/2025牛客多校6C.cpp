#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

//https://ac.nowcoder.com/acm/contest/108303
/*
    DP || 组合数学
    题意:
        对于一个排列P, 定义f(P)如下:
        function f(P):
            stack = []
            for element in P:
                while stack is not empty and stk.top() > element:
                    stack.pop()
                stack.push(element)
            return the size of stack
        给定一个整数n, 求所有长度为n的排列P'的(f(P'))^3的和, 结果对998244353取模
        范围: 多测, 组数T∈[1,1e5], n∈[1,5e5], 注意不保证∑n <= 5e5
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        函数f(P)本身是单调栈的实现方式, 显然这是个与单调栈可见性有关的题目
        从右向左看, 我们每次只能看到更小的元素
        因此我们可以枚举f(P')的值, 设当前P'从右向左看可以看到k个元素
        这等价于: 把排列P'划分成k个非空子数组, 每个子数组的最小元素在最右端, 其余元素任意排列
                 同时, 这k个非空子数组之间必须有序, 按照最小元素从小到大排
        例如2 1 4 3 5
        我们将把它划分成 2 1 | 4 3 | 5
        进一步地, 这等价于把排列P'划分成k个非空圆排列, 这是第一类斯特林数
        因此所求的就是 ∑(k^3 * s(n,k)), k∈[1,n]
        暴力预处理s(n,k)的时间复杂度是O(n^2), 我们可以用生成函数 + NTT优化到O(nlogn) [第一类斯特林数(行)]
        但对于本题这个式子, 我们还有更聪明的dp做法
        首先给出s(n,k)的递推式: s(n,k) = s(n - 1, k - 1) + (n - 1)s(n - 1, k)
        我们令A_p(n) = ∑(k^p * s(n,k))
        那么A_p(n) = ∑(k^p * s(n - 1,k - 1)) + ∑(k^p * (n - 1)s(n - 1, k))
        我们发现, 后一项就是(n - 1)A_p(n - 1)
        因此只需要考虑∑(k^p * s(n - 1,k - 1))
        令j = k - 1
        ∑((j+1)^p * s(n - 1, j))
        利用二项式展开, (j+1)^p = ∑(C(p,i) * j^i), i∈[0,p]
        因此转化成
            ∑∑C(p,i) * j^i * s(n - 1, j)
          = ∑C(p,i)∑j^i * s(n - 1, j)
          由于k = n时, s(n - 1, k) = s(n - 1, n) = 0
              k = 0时, s(n - 1, 0) = [n - 1 == 0]
          因此事实上, ∑j^i * s(n - 1, j) = ∑k^i * s(n - 1, k)
          则原式变为
          = ∑C(p,i) * A_i(n - 1)
        因此有:
            A_p(n) = ∑C(p,i) * A_i(n - 1) + (n - 1)A_p(n - 1)
        这可以用dp来求解
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int C[4][4];
const int N = 500000;
int dp[N + 1][4];
void solve() {
    int n;
    cin >> n;
    cout << dp[n][3] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 3; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = ((ll)C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    dp[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int p = 0; p <= 3; p++) {
            dp[n][p] = 1LL * (n - 1) * dp[n - 1][p] % MOD;
            for(int i = 0; i <= p; i++) {
                add(dp[n][p], 1LL * dp[n - 1][i] * C[p][i] % MOD);
            }
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
