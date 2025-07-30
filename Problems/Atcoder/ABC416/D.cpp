#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc416/tasks/abc416_d
/*
    贪心 || 数论 || 双指针
    题意:
        给定两个数组a,b和一个模数MOD, 你可以任意重排数组a
        求∑((a[i] + b[i]) % MOD)的最小值
        范围: N∈[1,3e5], MOD∈[1,1e9], a[i],b[i]∈[0,MOD - 1]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        根据数论知识, 我们要求的式子等价于∑(a[i] + b[i]) - 进位次数 * MOD
        也就是说, 我们要最大化a[i] + b[i] >= MOD的次数
        贪心地想, x越大, 越有可能发生进位, 这里就有着单调性
        我们可以把a,b进行排序
        从大到小枚举a的元素, 从小到大选取b中元素尝试与其进行匹配, 遇到进位算作匹配成功
        由于有单调性, 这样匹配一定是最优的, 于是就可以求解出答案
*/
void solve() {
    int n, MOD;
    cin >> n >> MOD;
    vector<int> a(n + 1), b(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
        ans += b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = n, l = 1; i >= 1; i--, l++) {
        while(l <= n && a[i] + b[l] < MOD) l++;
        if(l > n) break;
        ans -= MOD;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
