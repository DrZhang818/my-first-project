#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://ac.nowcoder.com/acm/contest/96366/G
/*
    前缀和 || 数学
    给定两个正整数𝑛和𝑚,其中1≤𝑛<𝑚≤10^9,定义函数:
        F(x)= ∑d (d|x)
    即𝐹(𝑥)为正整数𝑥的所有正约数之和。
    我们的目标是求出：∑𝑖=𝑛->𝑚 𝐹(𝑖) 并对结果取模 998244353
    
*/

const int MOD = 998244353;

ll sum_range(ll L, ll R){
    ll len = (R - L + 1);
    ll s = (L + R);
    ll res = (s % MOD) * (len % MOD) % MOD;
    ll inv2 = (MOD + 1) / 2;
    res = (res * inv2) % MOD;
    return res;
}

ll S(ll M){
    if(M == 0) return 0;
    ll res = 0;
    ll i = 1;
    while(i <= M){
        ll v = M / i;
        ll r = M / v;
        ll part = sum_range(i, r);
        part = (part * (v % MOD)) % MOD;
        res = (res + part) % MOD;
        i = r + 1;
    }
    return res;
}

void solve(){
    ll n, m;
    cin >> n >> m;
    ll ans = (S(m) - S(n - 1)) % MOD;
    if(ans < 0) ans += MOD;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    return 0;
}