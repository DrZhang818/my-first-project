#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2070/problem/A
/*
    数学 
    题意:
        给定一个整数n, 定义一个数x是合法的, 当且仅当x % 3 == x % 5
        计算[0,n]中有多少个数是合法的
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力, 枚举的复杂度为O(n), 验证为O(1), 故暴力的复杂度为O(n), 需要优化
        本题我们可以利用模运算的性质来优化
        对于这种双模问题, 可以发现LCM就是一个最小正周期
        因此我们只需要算出0~14中哪些数是合法的, >= 15的数都可以利用周期性来直接计算出来
        我们发现只有0/1/2是合法的
        那么计算[0,n]的公式为:
        n / 15 * 3 + rem[n % 15]
*/
void solve() { 
    int n;
    cin >> n;
    vector<int> rem(15);
    for(int i = 0; i < 15; i++) {
        rem[i] = i % 3 == i % 5;
        if(i > 0) rem[i] += rem[i - 1];
    }
    ll ans = n / 15 * 3 + rem[n % 15];
    cout << ans << "\n";
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
    
