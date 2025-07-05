#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


/*
    以下同一使用G代表gcd函数, 下面介绍gcd的基本运算性质
    (1)G(a, b) = G(a, a + b) = G(a, k * a + b)
    (2)G(k * a, k * b) = k * G(a, b)
    (3)G(a, b, c) = G(G(a, b), c)
    (4)若G(a, b) = d, 则G(a/d, b/d) = 1, 即a/d与b/d互素
    更相减损术:
        G(a, b) = G(a, a - b) = G(b, a - b)
        while(a != b) 
            if(a > b) a = a - b
            else b = b - a
        return a
    欧几里得递归计算GCD方法:
        G(a, b) = G(b, a % b)
    Stein Algorithm
        是对更相减损术的改进
*/
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void solve() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << "\n";
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
    
