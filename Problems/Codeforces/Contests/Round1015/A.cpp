#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/2084/problem/A
/*
    构造 || 数论
    题意:
        给定一个正整数N, 要求构造一个1~N的排列P, 满足:
        对于i∈[2,N], max(P[i-1], P[i]) mod i = i - 1
        如果无解, 输出-1
        范围: N∈[2,100]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先分析题目性质, 对于式子x ≡ i - 1(mod i)可以做以下变形:
        x+1-i ≡ 0(mod i) -> x + 1 ≡ 0(mod i), 这意味着i 是 x + 1的因子
        于是我们有个很自然的想法, 让x = i - 1就可以了
        _,1,2,3,...,n-1  这样一个排列能够满足i∈[3,N]的条件
        对于i = 2, _位置只能填n
        而max(n,1) = n, 因此需要2是n+1的因子, 那么n是奇数时就构造完成了
        当n是偶数时, 又该如何构造呢?
        考虑n摆放的位置
        (1)由上述讨论, n放在开头(i = 1)的位置肯定是不行了
            因为n + 1是奇数, 而奇数 ≡ 1(mod 2), 与条件矛盾
        (2)n放在结尾(i = n)
            由于n是整个排列中最大的数, 因此在结尾位置时, 需要满足
            n + 1 ≡ 0(mod n)
            而显然由模运算基本性质, n + 1 ≡ 1(mod n), 故无法满足
        (3)n放在中间位置(i = k, k∈[2,n-1])
            此时n有两个相邻位置, 且取max后得到的都是n
            因此i和i + 1都应是n + 1的因子, 即n + 1 ≡ 0(mod i * (i + 1))
            注意到i(i+1)一定是偶数, 但n + 1一定是奇数
            因此不可能满足上述等式
        综上, 对于n为偶数的情况是一定无解的, 特判无解情况即可
*/
void solve() { 
    int n;
    cin >> n;
    if(n % 2 == 0) {
        cout << -1 << "\n";
    } else {
        cout << n << " ";
        for(int i = 1; i <= n - 1; i++) {
            cout << i << " \n"[i == n - 1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
