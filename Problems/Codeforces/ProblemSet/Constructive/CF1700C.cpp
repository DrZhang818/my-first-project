#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1700/problem/C
/*
    构造 || 差分
    题意:
        给定一个长度为N的数组, 你可以进行以下三种操作:
        op1: 选择一个下标i, 使a[1:i]减1
        op2: 选择一个下标i, 使a[i:N]减1
        op3: 使整个数组加1
        求使得数组中每个元素都为0的最小操作次数
        范围: N∈[1,2e5], a[i]∈[-1e9,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构、
        首先观察题目性质, 我们的操作是区间加操作, 目标是让数组整体为0
        这正是差分的经典性质, 数组的单调性与差分数组的正负性是等价的
        我们可以在数组前加上一个虚拟元素0
        这样求出差分数组, 就等价于令差分数组全部为0 
        而操作随之变为:
        op1: 选择一个下标i, 让d[1]减1, d[i+1]加1
        op2: 选择一个下标i, 让d[i]减1 
        op3: 让d[1]加1
        不难发现, 我们可以从d[2:n]入手, 因为这些元素的调整只涉及op1和op2
        如果d[i] > 0, 那么我们必须利用op2, 操作次数为d[i]
        如果d[i] < 0, 那么我们必须利用op1, 操作次数为abs(d[i]), 同时d[1]+=d
        让d[2:n]全部为0后, 考虑d[1]
        如果d[1] > 0, 那么利用op1或op2, 都可以使d[1] = 0, 操作次数为d[1]
        如果d[1] < 0, 那么利用op3, 操作次数为abs(d[1])
*/

//jiangly 优化方法
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = 0, a1 = a[1];
    for(int i = 1; i < n; i++) {
        ll d = a[i + 1] - a[i];
        ans += abs(d);
        if(d < 0) {
            a1 += d;
        }
    }
    ans += abs(a1);
    cout << ans << "\n";
}

// void solve() {
//     int n;
//     cin >> n;
//     vector<ll> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     ll cur = 0;
//     for(int i = n - 1; i >= 1; i--) {
//         if(a[i] - cur > a[i + 1]) {
//             cur += a[i] - cur - a[i + 1];
//         }
//         a[i] -= cur;
//     }
//     ll ans = cur;
//     if(a[1] < 0) {
//         ans -= a[1];
//         for(int i = n; i >= 1; i--) {
//             a[i] -= a[1];
//         }
//     }
//     ans += a[n];
//     cout << ans << "\n";
// }

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
