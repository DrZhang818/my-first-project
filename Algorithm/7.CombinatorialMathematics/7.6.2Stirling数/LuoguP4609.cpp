#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 50000;

//https://www.luogu.com.cn/problem/P4609
/*
    组合数学
    题意:
        给定N,A,B, 定义一个长度为N的排列是合法的, 当且仅当从左向右能看到A个数, 从右向左能看到B个数
        如果i的左(右)边没有任何数比它大, 则i可以从左(右)边看到
        求有多少种合法的排列, 结果对1000000007取模
        范围: N∈[1,5e4], A,B∈[1,100], T∈[1,2e5]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        对于这种可见性问题, 我们要自然地把它与单调栈联系起来
        显然, 无论从左向右还是从右向左, 栈顶元素必然是最大的数, 最大的数把排列分成了两部分
        我们不妨先考虑从左向右看到的A个数, 称这些数为"极大数"
        每个极大数会遮挡住右边若干个数, 直到遇见下一个比它更大的"极大数"
        此时我们发现, 这若干个被遮挡的数, 无论怎么排列, 都会被遮挡, 设有M个被遮挡, 那么方案数为M!
        我们把遮挡它们的"极大数"也算在其中, 但其位置固定, 这M个数方案数为(M-1)!, 这是圆排列的方案数
        因此从左到右看到的A个数, 可以理解为A个圆排列
        从右向左看到的B个数, 理解为B个圆排列
        我们把最大的数拿出来, 就变成左边放(A-1)个圆排列, 右边放(B-1)个圆排列
        把n个数划分成m个圆排列的方案数是S[n][m], 即第一类Stirling数
        那么把(N-1)个数分成(A+B-2)个圆排列方案数为S[N-1][A+B-2]
        左边放A-1个, 右边放B-1个, 因此组合数为C[A+B-2][A-1]
        二者相乘就是答案
        注:
            S[n][m] = S[n - 1][m - 1] + (n - 1) * S[n - 1][m]
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int S[N + 1][201];
int C[201][101];
void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    cout << 1LL * S[n - 1][a + b - 2] * C[a + b - 2][a - 1] % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    S[0][0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= 200; j++) {
            S[i][j] = S[i - 1][j - 1];
            add(S[i][j], 1LL * (i - 1) * S[i - 1][j] % MOD);
        }
    }
    for(int i = 0; i <= 200; i++) {
        for(int j = 0; j <= i && j <= 100; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = ((ll)C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
