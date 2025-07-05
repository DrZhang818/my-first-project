#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2104/problem/A
/*
    数学
    题意:
        给定三堆牌, 各有a,b,c张牌, 你可以从第三堆牌中选出k张分配到第一、二堆中, 
        问最终能否让三堆牌数量相等
        范围: 1 <= a < b < c <= 1e8, k∈[1,c]
    关键思考:
        本题为计算类题目, 常用思考方式为: 暴力->DP||数学, 常用优化手段为: 二分、前缀和、数学
        显然总牌数必须是3的倍数
        这属于a,b只能增, c只能减的任意分配问题, 步长为1, 至少分配一次
        因此只需满足a < tar, b <= tar, c > tar即可
        由于有a < b < c这个限制, 可以简化为b <= tar, 此时一定保证了a < tar和c > tar
*/
void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int tot = a + b + c;
    if(tot % 3 == 0 && b <= tot / 3) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
