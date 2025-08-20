#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P3200
/*
    组合数学 || Catalan数
    题意:
        定义一个长度为2N的排列是有趣的, 当且仅当满足以下要求:
        (1)所有的奇数项满足a[1] < a[3] < ... < a[2N - 1]
        (2)所有的偶数项满足a[2] < a[4] < ... < a[2N]
        (3)任意相邻的两项a[2i-1]与a[2i]满足: a[2i-1] < a[2i]
        对于给定的N, 请你求出有多少个不同的长度为2N的有趣的排列, 结果对P取模
        范围: N∈[1,1e6], P∈[1,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力方法, 枚举所有排列并验证, 时间复杂度为O(N * (2N)!), 超时
        观察题目性质, 我们发现这题本质是在计算把2N个数分出两个大小为N的集合, 看哪些划分方法符合条件(3)
        这是因为, 对于一个集合S, 将其递增排序后是唯一的, 因此对于任意一种划分方式, 在(1)(2)的约束下只有
        唯一的排列方式
        考虑条件(3)的性质:
        条件(3)要求任意相邻的奇数位置元素小于偶数位置元素, 我们考虑从小到大构造:
        对于每个元素, 有且仅有两种放置方法: 放在下一个奇数位 or 放在下一个偶数位
        否则如果跳过这两个位置, 就必然违反条件(1)(2)
        我们把模型进行抽象, 在N × N的网格中, 我们当前位于(0,0), 要到达(N,N)
        放在下一个奇数位视为向右走一格, 放在下一个偶数位视为向上走一格
        则条件(3)等价于: 从(0,0)到(N,N)的路线不能穿过对角线
        证明很简单: 我们考虑穿过对角线的前一时刻, 我们处在对角线上的(i,i)位置
        此时的含义是: 1~2i被填放到了a[1]~a[2i]
        我们穿过对角线, 说明把2i + 1填到了a[2i + 2]
        由于2i + 2 ~ 2N中的任何数都比2i + 1大, 因此没有任何方案可以满足条件(3), 矛盾
        于是问题被规约到经典的Catalan棋盘模型了, 问题答案即 C(N)
        但本题难点在于, 模数P不保证质数, 而Catalan数的O(n)计算方法都涉及除法, 如何解决这个问题呢?
        我们关注Catalan的这一个公式:
            Catalan(N) = C(2N,N) / (N + 1), 其中C(n,r)表示组合数
        对其进行变形:
              (2N)! / (N+1)(N!)(N!)
            = Πi [i:N+2->2N] / Πi [i:1:N]
        我们可以利用 分解质因数 + 约分 的方式求出这个式子的值
*/
vector<int> minp, primes;
void init(int n) {
    minp.resize(n + 1);
    for(int i = 2; i <= n; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > n) {
                break;
            }
            minp[i * p] = p;
            if(minp[i] == p) {
                break;
            }
        }
    }
}
int fast_pow(int a, int b, int MOD) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, p;
    cin >> n >> p;
    init(2 * n);
    vector<int> cnt(2 * n + 1);
    for(int i = n + 2; i <= 2 * n; i++) {
        int x = i;
        while(x != 1) {
            cnt[minp[x]]++;
            x /= minp[x];
        }
    }
    for(int i = 1; i <= n; i++) {
        int x = i;
        while(x != 1) {
            cnt[minp[x]]--;
            x /= minp[x];
        }
    }
    int ans = 1;
    for(int i = 1; i <= 2 * n; i++) {
        if(cnt[i]) {
            ans = 1LL * ans * fast_pow(i, cnt[i], p) % p;
        }
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
