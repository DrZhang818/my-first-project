#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2048/problem/A
/*
    数学
    题意: 给定一个整数x, 你可以进行若干次一下操作
        op1: 按照数位, 选择两个相邻数位都为3的位置, 移除
        op2: x减33
        判断能否让x变为0
    关键思考:
        分析两种操作的性质
        op2比较简单, 重复做op2相当于x % 33
        op1是对数位进行操作
            考虑把x写成以下形式
            A33B
            let t := B / 10
            即t表示B的位数
            那么x = A*10^(t+2) + 33*10^t + B
            进行一次op1后x变为
            AB
            即A*10^t + B;
        二者做差得到
            99A*10^t + 33*10^t
        这就是op1的实际效果, 可以发现本质上就是进行了很多次的op2
        而这个过程始终保持在模33意义下不变
        因此只需要判断x % 33 == 0即可
*/

void solve(){
    int n;
    cin >> n;
    if(n % 33 == 0){
        cout << "YES\n";
    }   
    else{
        cout << "NO\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
