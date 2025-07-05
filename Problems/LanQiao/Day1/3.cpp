#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.lanqiao.cn/problems/5752/learning/?contest_id=235
/*
    组合数学
    题意:
        给定n个位置, 共有m种状态, 每个位置有且仅有1个状态
        要求计算出有多少种情况满足存在相邻两个位置状态相等
    关键思考:
        正难则反, 思考有多少种情况可以使得任意相邻位置状态不相等
        总状态个数是m^n
        如何计算任意相邻位置状态不相等的个数?
        考虑第一个位置可以选m个, 则第二个状态必然是剩下的m-1, 第三个也是m-1,...
        于是个数就是 m * (m-1)^(n-1)
        使用带模快速幂计算即可
*/
const ll MOD = 100003;
ll power_pow(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve(){
    ll m, n;
    cin >> m >> n;
    ll tot = power_pow(m, n, MOD);
    ll no = power_pow(m - 1, n - 1, MOD);
    no = m * no % MOD;
    ll ans = (tot - no + MOD) % MOD;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}