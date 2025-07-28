#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/AT_abc114_d
/*
    数论
    题意:
        给定一个整数N, 在N!的所有因子中, 有多少个合法数字
        一个数字是合法的, 当且仅当这个数字恰好有75个因子
        范围: N∈[1,100]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 前缀和、双指针、数学
        首先思考如何求解一个数的因子数量d(n)
        我们把n进行质因数分解
        例如将24拆为2^3 * 3^1
        有个显然的性质是, x^k有k+1个因子
        而由于d(n)是积性函数, 那么就可以拆为
        d(24) = d(8) * d(3) = 4 * 2 = 8
        反过来, 如果我们已知因子数量, 如何求有多少个符合条件的数呢
        我们把75进行分解
        75 = 75
           = 25 * 3
           = 15 * 5
           = 5 * 5 * 3
        分别统计四种情况即可, 例如25 * 3
        我们要找出有多少个质数的幂次 >= 24, 有多少个质数的幂次 >= 2
        然后根据乘法原理计算即可, 注意利用容斥原理, >=2的个数要减1, 因为>=24的必然也是>=2的
*/
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(105);
    for(int i = 1; i <= n; i++) {
        int ti = i;
        for(int j = 2; j * j <= ti; j++) {
            while(ti % j == 0) {
                cnt[j]++;
                ti /= j;
            }
        }
        if(ti != 1) cnt[ti]++;
    }
    int c2 = 0, c4 = 0, c14 = 0, c24 = 0, c74 = 0;
    for(int i = 2; i <= 100; i++) {
        if(cnt[i] >= 2) {
            c2++;
        }
        if(cnt[i] >= 4) {
            c4++;
        }
        if(cnt[i] >= 14) {
            c14++;
        }
        if(cnt[i] >= 24) {
            c24++;
        }
        if(cnt[i] >= 74) {
            c74++;
        }
    }
    ll ans = 0;
    if(c4 >= 2) {
        ans += c4 * (c4 - 1) / 2 * (c2 - 2);
    }
    if(c14 >= 1) {
        ans += c14 * (c4 - 1);
    }
    if(c24 >= 1) {
        ans += c24 * (c2 - 1);
    }
    if(c74 >= 1) {
        ans += c74;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
