#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc419/tasks/abc419_e
/*
    DP
    题意:
        给定一个长度为N的数组和两个整数M,L, 定义一个数组是合法的, 当且仅当数组的每个长度为L的子数组
        的和都是M的倍数, 你可以进行以下操作:        
        op: 选择数组中的一个数, 使其加1
        求最少需要几次操作使得数组变为合法的数组
        范围: N,M∈[1,500], L∈[1,N], a[i]∈[0,M)
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心||网络流, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 不难发现, 数组在模M意义下是个循环数组
        于是我们有了暴力做法: 枚举前L个位置的在模M下的值, 时间复杂度为O(N * M^L), 超时
        瓶颈在于枚举, 我们从一个easy版本来思考如何优化:
        假设N = L, 此时能否有所优化呢?
        答案是肯定的, 我们发现此时就无需保存每个位置具体选了什么这个信息了, 我们只关心它们加起来的结果
        本质上是个分组背包问题, 定义dp[i][s] := 考虑前i个数, 总和模M为s时的最小代价
        转移时枚举第i个数选什么, dp[i][(s + x) % M] = dp[i-1][s] + cost(i,x)
        想清楚这个问题, 我们再来看原问题: N >= L时如何做
        关键性质是数组为循环数组, 当我们确定a[i] % M = x后, 等价于确定了a[i + kL] % M = x 
        因此转移方程变为:
            dp[i][(s + x) % M] = dp[i-1][s] + ∑cost(i + kL,x)
        我们可以在O(NM)时间内预处理 ∑cost(i + kL,x)
        最终问题在 O(NM + LM^2)时间内得到了解决
*/  
int m;
int mod(int x) {
    return (x % m + m) % m;
}
void solve() {
    int n, L;
    cin >> n >> m >> L;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector cost(L + 1,  vector<int>(m));
    for(int i = 1; i <= L; i++) {
        for(int j = i; j <= n; j += L) {
            for(int s = 0; s < m; s++) {
                cost[i][s] += mod(s - a[j]);
            }
        }
    }
    vector<int> dp(m, inf);
    dp[0] = 0;
    for(int i = 1; i <= L; i++) {
        vector<int> ndp(m, inf);
        for(int x = 0; x < m; x++) {
            for(int y = 0; y < m; y++) {
                ndp[mod(x + y)] = min(ndp[mod(x + y)], dp[x] + cost[i][y]);
            }
        }
        swap(dp, ndp);
    }
    cout << dp[0] << "\n";
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
