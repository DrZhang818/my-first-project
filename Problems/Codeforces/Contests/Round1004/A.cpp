#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2067/problem/A#
/*
    构造 || 数学
    题意:
        给定两个整数x,y, 判断是否存在一个整数n, 使得S(n) = x, S(n + 1) = y
        定义S(a)表示十进制数a的数位和
        范围: x,y (1 ≤ x ≤ 1000, 1 ≤ y ≤ 1000).
    关键思考:
        由于与数位和有关, 我们考虑展开数位和
        num = a[n]*10^n + a[n-1]*10^(n-1) + ... + a[1]*10 + a[0]
        S(num) = a[n] + a[n-1] + ... + a[1] + a[0]
        考虑n + 1与n的关系
        (1)如果不发生进位, 那么就相当于a[0]增加1
        (2)如果发生1次进位, 那么a[0]-9, a[1]+1 --> Δ = -8
        (3)如果发生k次进位, 那么a[0],a[1],...,a[k-1]-9, a[k]+1 --> Δ = -9k + 1
        因此x - y的值域为{-1, 8, 17, ..., 9k-1}
        从而存在整数n的必要条件为:
            x - y + 1 >= 0 && (x - y + 1) % 9 == 0;
        下面证明充分性:
        可以把a[n] + a[n-1] + ... + a[1] + a[0] = x看作n维基底作线性组合
        设(x - y + 1) / 9 = k
        那么我们只需要让a[0],a[1],...,a[k - 1]全部为9, 且a[k]不能为9
        并且a[0]~a[k]的累加和 = 9 * k + y - 1
        就可以构造出一个合法的n
*/
void solve(){
    int x, y;
    cin >> x >> y;
    if(x - y + 1 >= 0 && (x - y + 1) % 9 == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

