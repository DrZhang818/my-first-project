#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

//https://codeforces.com/problemset/problem/1603/B
/*
    构造
    题意:
        给定两个偶数x,y, 找出一个正整数n, 满足n mod x = y mod n
        范围: x,y∈[2,1e9], n∈[1,2e18]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 由于式子比较简单, 我们优先考虑打表找规律
        (1)经过打表, 我们发现对于y < x的情况, x + y总是可行的
        这是因为(x + y) % x = y, y % (x + y) = y, 因此x + y就是y < x时的一个合法解
        (2)对于y = x的情况非常简单, 取n = x = y即可
        (3)本题最难处理的就是y > x的情况, 打表也找不到任何规律, 下面介绍一种思考
           模运算的方法
        我们可以把x, y画在一维数轴上
        0___x______y
        接下来粗略估计一下n的上下界
        首先n不能小于x, 否则n % x = n, y % n < n, 矛盾
        其次n不能大于y, 否则y % n = y, n % x < x, x < y, 矛盾
        下面就是这种方法的核心思想:
        我们以x为步长划分整个数轴
        0___x___x__y
        接下来我们就会发现, n % x的值就可以表示为n与左侧离n最近的x之间的距离
        y % n的值就表示为y与左侧离y最近的n之间的距离
        由于n是不定的, 我们从最简单的情况考虑, 即n > y / 2
        此时y的左侧只有一个n, 距离的表示更为清晰
        能否再简单一些呢? 我们把x扩展后, 只考虑最后一段[x,y], 即选择离y最近的x
        这样我们就会发现, n % x 和 y % n都可以用这一段区间来表示, 并且恰好有
        n % x + y % n = y % x
        由于y和x都是偶数, 那么y % x必然也是个偶数, 因此区间是可以等分的
        那么就让n % x = y % n = (y % x) / 2
        此时n = y - (y % x) / 2
        这样就完成了y > x情况的构造 
*/
void solve() { 
    ll x, y;
    cin >> x >> y;
    if(y < x) {
        cout << y + x << "\n";
        return;
    }
    ll n = y - (y % x) / 2;
    cout << n << "\n"; 
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
    
