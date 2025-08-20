#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1244/problem/C
/*
    构造 || 数论
    题意:
        定义一场比赛的得分规则为:
        (1)平局, 双方获得d分
        (2)分出胜负, 获胜方获得w分, 失败方获得0分
        你的队伍参加了N场比赛, 总得分为P, 请你构造出一个三元组(x,y,z), 分别表示获胜次数、平局次数、
        失败次数, 满足w * x + d * y = P 且 x + y + z = N
        无解输出 -1
        范围: N∈[1,1e12], P∈[0,1e17], 1 <= d < w <= 1e5
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先思考暴力做法, 枚举x,y, 验证是否符合要求, 时间复杂度为O(N^2), 超时
        瓶颈在于枚举, 由于N太大, 我们一个都不能枚举
        观察问题结构, w * x + d * y = P是一个线性丢番图方程, 我们可以用exgcd来求解
        我们希望找到该方程的一组非负整数解, 并且要最小化x + y, 以便让z也有非负整数解
        由于d < w, 我们可以考虑进行式子变形
        (w - d) * x + d * (x + y) = P
        最小化 x + y <==> 最大化 x <==> 最小化 y
        我们有办法直接求出 y 的最小非负整数解
        把线性丢番图转化为同余方程
        d * y ≡ P (mod w)
        有解的充分必要条件为 gcd(d,w) | P
        我们令g = gcd(d,w), 为求解这个同余方程, 我们转化成等价形式
        令 a = d/g, b = P/g, c = w/g
        那么就等价于求解:
            a * y ≡ b (mod c), 其中a,c互质
        这就可以用模逆元求解了
            y ≡ b * a^{-1} (mod c)
        求解模逆元直接使用exgcd即可
        得到最小的y后, 我们可以直接得出 
        x = (P - d * y) / w
        z = N - x - y
        判断是否有x >= 0 && z >= 0即可
*/
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll mod_inv(ll a, ll p) {
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
ll get(ll a, ll b, ll c) {
    b = (b % c + c) % c;
    ll g = gcd(a, c);
    if(b % g != 0) {
        return -1;
    }
    a /= g;
    b /= g;
    c /= g;
    return b * mod_inv(a, c) % c;
}
void solve() {
    ll n, p, w, d;
    cin >> n >> p >> w >> d;
    ll y = get(d, p, w);
    if(y == -1) {
        cout << -1 << "\n";
        return;
    }
    ll x = (p - d * y) / w;
    ll z = n - x - y;
    if(x < 0 || z < 0) {
        cout << -1 << "\n";
        return;
    } 
    cout << x << " " << y << " " << z << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
