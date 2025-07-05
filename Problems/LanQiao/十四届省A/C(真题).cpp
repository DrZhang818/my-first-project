#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.lanqiao.cn/problems/3502/learning
/*
    数学
    题意:
        定义一个数x是合法的, 当且仅当存在整数y,z, 使得x = y^2 - z^2
        给定L,R, 计算[L,R]内有多少个合法的数
        L,R∈[1,1e9]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察数字x的性质, 变形式子可得, x = (y + z) * (y - z)
        令p = y + z, q = y - z
        得到y=(p+q)/2, z=(p-q)/2
        因此我们可以做如下等价转化:
        x合法 <--> 存在整数y,z <--> 存在p*q = x, 且p+q,p-q为偶数
        所以事实上我们只需要判断x的因子中是否有一对相加为偶数
        由于情况比较复杂, 我们从反面思考哪些数字不存在任意一对相加为偶数
        相加为奇数意味着一奇一偶, 因此我们考虑构造:
        2*1, 2*3, 2*5, 2*7, ...
        2, 6, 10, 14, ...这些数字被表示为2 * (2k-1), 无论怎么分配因子都是一奇一偶
        简化后得到X = {4k - 2}, k >= 1
        而求[L,R]的合法数量等价于[1,R] - [1,L-1]
        因此我们考虑如何求解 f(i) := [1,i]内的合法数量
        只需要求解4k - 2 <= i
        即k <= floor((i + 2) / 4)
*/
ll cnt(ll x) {
    return (x + 2) / 4;
}
// bool ok(ll x) {
//     bool flag = false;
//     for(int i = 1; i * i <= x; i++) {
//         if(x % i == 0) {
//             if((i + (x / i)) % 2 == 0) {
//                 flag = true;
//                 break;
//             }
//         }
//     }
//     return flag;
// }
void solve() { 
    ll l, r;
    cin >> l >> r;
    // ll ans = 0;
    // for(ll i = l; i <= r; i++) {
    //     if(!ok(i)) {
    //         cout << i << "\n";
    //     } else{
    //         ans++;
    //     }
    // }
    ll p = cnt(r) - cnt(l - 1);
    cout << r - l + 1 - p << "\n";
    // cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
