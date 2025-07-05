#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://atcoder.jp/contests/arc060/tasks/arc060_b
/*
    构造 || 数学 || 思维 + 暴力
    题意:
        给定一个整数n和一个整数s, 定义F(b, n)的值为n在b进制下的数位和
        求出最小的b, 满足F(b,n) == s, 若没有符合条件的b, 输出-1
        范围: n,s ∈ [1,1e11]
    关键思考:
        本题是一道考察对进制理解的好题
        首先我们发现验证一个b是否合法的时间是log级的, 因此这提示我们可以尝试使用
        暴力方法来求解. 但数据范围很大, 我们最多只能对1e6~1e7范围内进行暴力
        剩下的范围怎么计算呢?
        由于是求最小值问题, 比较自然的想法是思考能否找到某种单调性进行二分, 或者dp之类的
        但由于本题满足条件的b是离散的, 所以这些方法全部失效了
        这时候就要想到往数学上进行思考了
        对于b > 1e6的范围, 因为n和s都<=1e11
        所以对进制比较熟悉的就能想到, 在base进制大于1e6的时候, 1e11范围内的数在base进制下最多两位
        这是因为一个数num在base进制下的表示为
            num = a0*base^n + a1*base^(n-1) +...+ an*base^0
            base^2的范围就已经大于1e12了, 因此指数 >= 2的部分一定系数为0
        那么n就可以表示为 n = p*base + q
        s = n % base + (n // base) % base, 由同余原理, n % base == q, n // base == p
        因此s = p + q;
        那么做差之后, n - s = p * (base - 1)
        我们只需要枚举n - s的因子 + 1, 在log时间内验证base即可
        注意特判n == s的情况, 此时只要p取0, base就有任意组解, 但我们无法通过枚举因子来获取
        此时由于p == 0, 则n == s == q
        那么由于q一定小于base(否则会进位, 与q为0矛盾)
        所以base > n
        那么就取最小的base = n + 1即可满足
*/
void solve(){
    ll n, s;
    cin >> n >> s;
    if(n == s) {
        cout << n + 1 << "\n";
        return;
    }
    auto dfs = [&](auto &&dfs, ll b, ll cur_n) -> ll {
        if(cur_n < b) {
            return cur_n;
        }
        return dfs(dfs, b, cur_n / b) + (cur_n % b);
    };
    for(ll i = 2; i <= 1000000; i++) {
        if(dfs(dfs, i, n) == s) {
            cout << i << "\n";
            return ;
        }
    }    
    ll x = n - s;
    ll b = LLONG_MAX / 2;
    for(ll i = 1; i * i <= x; i++) {
        if(x % i == 0) {
            if(i + 1 > 1000000 && dfs(dfs, i + 1, n) == s) {
                b = min(b, i + 1);
            }
            if((x / i) + 1 > 1000000 && dfs(dfs, (x / i) + 1, n) == s) {
                b = min(b, (x / i) + 1);
            }
        }
    }
    if(b != LLONG_MAX / 2) {
        cout << b << "\n";
        return;
    }
    cout << -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}