#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 2000000007;

//https://acm.hdu.edu.cn/showproblem.php?pid=4379
/*
    贪心 || 枚举
    题意: 
        给定N,L,A,B,MOD, 定义一个长度为N的数列X, 满足X[i] = (A * i + B) % MOD
        定义序列Y是合法的, 当且仅当对于任何一对不同的i,j, 有Y[i] + Y[j] <= L, 且子序列每个元素
        本身也不超过L
        求数列X的最长合法子序列的长度
        范围: N∈[1,2e7], L∈[1,2e9], A,B,MOD∈[1,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 子序列Y要满足Y[i] <= L, 且Y[i] + Y[j] <= L
        利用这个条件, 我们可以把X[i]进行分类:
        (1)X[i] > L:
            这种X[i]直接扔掉
        (2)L/2 < X[i] <= L:
            这种X[i]最多取一个, 贪心地想, 我们取其中最小的一个
        (3)X[i] <= L/2:
            这种X[i]能取就取
        (2)(3)两种会对答案做贡献, 但当种类(3)的max + 种类(2)的min > L时, 二者是不相容的
        这时就用到(2)的一个性质, (2)的贡献最大为1, 因此如果因为(3)取了个较大的数导致(2)不能取
        我们就可以舍弃掉(2), 答案仍然是最优的
        生成数列X时我们要用递推的方式, 避免取模过慢
*/
int n, L, A, B, MOD;
void solve() {
    ll mn = inf, mx = 0;
    ll x = (A + B) % MOD;
    A %= MOD;
    B %= MOD;
    ll sum = 0;
    for(int i = 1; i <= n; i++, x += A) {
        if(x >= MOD) x -= MOD;
        if(x > L - x) {
            mn = min(mn, x);
        } else {
            mx = max(mx, x);
            sum += 1;
        }
    }
    if(mn + mx <= L) sum++;
    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n >> L >> A >> B >> MOD) {
        solve();
    }
    return 0;
}
