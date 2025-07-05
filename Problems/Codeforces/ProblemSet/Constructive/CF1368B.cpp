#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1368/problem/B
/*
    构造 || 数学 || 贪心
    题意:
        给定一个整数k, 要求构造一个长度最短的字符串, 满足子序列"codeforces"至少出现k次
    关键思考:
        由于需要构造长度最短, 因此要找到一种贪心策略, 使得每增加一个字符, 获得的收益最大
        注意到以下性质
        (1)不在"codeforces"内的字符一定不能加
        (2)在"codeforces"的基础上如何扩充?
           需要保证新加的字符在正确的位置上, 如新加入'f'只能在原来的'f'旁边加入
           这是因为可以把串拆分为"_____f_____", 可以理解为前后缀分解, 从前面选"code"
           从后面选"orces", 如果我们把'f'放在错误地位置, 那一定会减少"code"或"orces"的
           方案数, 如"_____f(or)__f(ces)_____"这样第二个f就利用不到他前面的"or", 导致变劣
        (3)最后的方案数根据乘法原理, 就等于个位置字符出现次数的乘积
        (4)长度固定, 即∑(cnt[i])固定, 要最大化Π(cnt[i])
           由均值不等式, 当每个cnt[i]趋同时, 乘积最大
        在以上性质基础上, 不妨举k = 129这个例子
        一种最优解为
        2 2 2 2 2 2 2 2 1 1
        我们可以采取补的方式, 先构造出需要的最低值x, 再在此基础上看看需要补充几个(x+1)
        形式化的, 记最低值为x
        那么有x^10 <= k, 即x = (int)pow(k, 0.1)
        在此基础上, 记最终x+1的出现次数为p, 则x的出现次数为10-p
        即(x+1)^p * x^(10-p) >= k (注意这里需要手写快速幂, 系统自带的会出现精度问题)
        枚举即可
        另外比较巧妙地解法是, 维护当前的乘积prod
        利用循环即可轻松构造出每个位置的次数
*/
//优化解法(tourist)
void solve1(){
    ll k;
    cin >> k;
    string s = "codeforces";
    int n = s.size();
    vector<ll> a(n, 1);
    ll prod = 1;
    for(int i = 0; prod < k; i = (i + 1) % n){
        prod = prod / a[i] * (a[i] + 1);
        a[i]++;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < a[i]; j++){
            cout << s[i];
        }
    }
    cout << "\n";
}
//自己的做法
ll LL_pow(ll a, ll b){
    ll res = 1;
    while(b > 0){
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
void solve(){
    ll k;
    cin >> k;
    string s = "codeforces";
    ll p = (ll)pow(k, 0.1);
    ll q;
    for(q = 0; q <= 10; q++){
        if(LL_pow(p + 1, q) * LL_pow(p, 10-q) >= k) break;
    }
    for(int i = 0; i < q; i++){
        for(int j = 0; j < p + 1; j++){
            cout << s[i];
        }
    }
    for(int i = q ; i < 10; i++){
        for(int j = 0; j < p; j++){
            cout << s[i];
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}
