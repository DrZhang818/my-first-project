#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2110/problem/A
/*
    数论 || 暴力枚举
    题意:
        给定一个长度为N的数组, 你可以进行以下操作:
        op: 删除数组中的一个元素
        定义一个数组a是合法的, 当且仅当min(a) + max(a) ≡ 0 (mod 2)
        求解最少需要进行几次操作使得数组合法
        范围: N∈[1,50], a[i]∈[1,50]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 显然删除中间元素是劣的, 我们要让每次操作的都是最值
        下面证明从两头同时删除是劣的
        假设第i次操作删除了mn, 第i + 1次操作删除了mx
        (1)如果mn和mx奇偶性相同, 则最优是两个都不删
        (2)mn和mx奇偶性不同的时候
            <1>如果mn删完后的新的mn'与mx奇偶性相同, 则无需删除mx
            <2>如果mn删完后的新的mn'与mx奇偶性不同
                如果删除mx后得到的mx'与mn'奇偶性相同, 则不删mn只删mx更优
                如果删除mx后得到的mx'与mn'奇偶性不同, 则不删mn只删mx更优
        这表明在任何时候, 转换删除方向都是不优的, 那么我们只需要枚举两种删除方向即可
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int ans = inf, cur = 0;
    for(int i = 1; i <= n; i++) {
        if((a[i] + a[n]) % 2) cur++;
        else break;
    }
    ans = cur;
    cur = 0;
    for(int i = n; i >= 1; i--) {
        if((a[1] + a[i]) % 2) cur++;
        else break;
    }
    ans = min(ans, cur);
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
