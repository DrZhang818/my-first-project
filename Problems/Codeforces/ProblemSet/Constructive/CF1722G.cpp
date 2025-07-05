#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1722/G
/*
    构造 || 位运算
    题意: 
        给定一个整数N, 你需要构造一个长度为N的数组a, 满足:
        (1)a[i]∈[0,2^31 - 1]
        (2)奇数位异或和等于偶数位异或和
        (3)所有数字互不相同
        范围:N∈[3,2e5]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先思考题目性质, "奇偶性"是对数组的一个划分, 下面介绍划分的异或和性质:
        设任意一种划分方式将数组划分成两个不交的子序列A,B
        那么XOR(A) = XOR(B) <==> XOR(a) = 0
        即两个不交的子序列异或和相等等价于总数组异或和为0
        这是由异或的良好性质保证的:
        XOR(X) ^ XOR(Y) = 0 <==> XOR(X) = XOR(Y)
        因此我们的问题就转化为: 用N个不同的数字构造出一个异或和为0的数组
        那问题就变得十分简单了
        可以用0~n-2作为前n-1个数字, 并求出异或和sum
        让sum作为第n个数字
        由于sum可能与前n-1个数字重叠, 只需要稍微调整即可
        如果sum与第1个数相同, 那就让调第2个数
        否则就调第1个数
*/

//trick [0,n]的异或和
/*
    考虑x = n % 4
    (1)x = 0:
        ans = n
    (2)x = 1:
        ans = 1
    (3)x = 2:
        ans = n + 1
    (4)x = 3:
        ans = 0
*/

//优化解法
void solve() {
    int n;
    cin >> n;
    vector<int> ans(n);
    int sum = 0;
    for(int i = 0; i < n - 1; i++) {
        ans[i] = i;
        sum ^= i;
    }
    if(sum == 0) {
        ans[1] |= 1 << 20;
    } else {
        ans[0] |= 1 << 20;
    }
    ans[n - 1] = sum | 1 << 20;
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
}



// void solve() {
//     int n;
//     cin >> n;
//     if(n & 1) {
//         if(n >> 1 & 1) {
//             cout << 1 << " ";
//         } else {
//             cout << 0 << " ";
//         }
//         for(int i = 2; i <= n; i++) {
//             cout << i << " \n"[i == n];
//         }
//     } else {
//         if(n >> 1 & 1) {
//             cout << 1 << " " << 2 << " " << 3 << " ";
//             cout << 4 << " ";
//             for(int i = 2; i <= n - 3; i++) {
//                 cout << (i << 2) << " \n"[i == n - 3];
//             }
//         } else {
//             for(int i = 0; i <= n - 1; i++) {
//                 cout << i << " \n"[i == n - 1];
//             }
//         }
//     }
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
