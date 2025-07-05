#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/2084/problem/B
/*
    构造 || 数论
    题意:
        给定一个长度为n的数组a, 判断是否可以通过重新排列数组, 使得存在一个下标i
        满足min(a[:i]) = gcd(a[i+1:]), i∈[1,n)
        范围: n∈[2,1e5], a[i]∈[1,1e18]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 我们记数组最小值为mn, 那么由min和gcd函数的性质可知
        当mn∈a[:i]时, min(a[:i]) = mn
        当mn∈a[i+1:]时, gcd(a[i+1:]) <= mn
        由于题目允许重排数组, 因此不难想到, 如果mn的个数 >= 2
        我们可以把其中一个放在数组末尾(i = n)
        这样取i = n - 1, 必有min(a[:n-1]) = mn = gcd(a[n])
        下面讨论mn恰有1个时的情况
        显然此时mn必须放在a[:i], 否则min(a[:i]) > mn >= gcd(a[i+1:]), 不成立
        而mn放在a[:i], 这意味着等式左侧恒等于mn, 则转化为gcd(a[i+1:]) = mn
        这等价于从除了mn外的剩下n-1个数中, 寻找一些数bi, 满足gcd(bi) = mn
        运用经典gcd恒等式, 这等价于gcd(bi/mn) = 1
        因此问题进一步化为判断被mn整除的数中是否可以选出一些数使得gcd/mn等于1
        而由gcd的运算具有单调性可知, gcd运算中增加一个数, 导致的结果是单调不升的
        因此等价于所有被mn整除的数取gcd, 看结果/mn是否为1
*/
inline ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll mn = 1e18;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mn = min(mn, a[i]);
    }
    ll ok = 0, g = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == mn && !ok) {
            ok = 1;
            continue;
        }
        if(a[i] % mn == 0) {
            if(g == 0) g = a[i] / mn;
            else g = gcd(g, a[i] / mn);
        }
    }
    if(g == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
    
