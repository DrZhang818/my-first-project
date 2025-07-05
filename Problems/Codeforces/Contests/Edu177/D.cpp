#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/2086/problem/D
/*
    DP || 组合数学
    题意: 
        给定一个长度为26的数组cnt
        一个字符串是合法的, 当且仅当字符串每个字母的出现频次与cnt数组一致
        并且任意相同字母的下标间隔为偶数
        你需要计算可以构造出的合法字符串数量, 结果对998244353取模
        范围: cnt[i]∈[0,5e5], ∑cnt∈[1,5e5]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学


*/
constexpr ll MOD = 998244353;
constexpr int N = 500005;
vector<ll> fac, inv_fac;
ll pow_mod(ll x, ll y) {
    ll res = 1;
    x %= MOD;
    while(y) {
        if(y & 1) res = res * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return res;
}
void init() {
    fac.resize(N + 1);
    inv_fac.resize(N + 1);
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        inv_fac[i] = pow_mod(fac[i], MOD - 2);
    }
}
void solve() { 
    int n = 0, m = 26;
    vector<int> cnt(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> cnt[i];
        n += cnt[i];
    }
    vector<ll> dp(n / 2 + 1);
    dp[0] = 1;
    for(int i = 1; i <= m; i++) {
        if(cnt[i] == 0) continue;
        for(int j = n / 2; j >= cnt[i]; j--) {
            dp[j] = (dp[j] + dp[j - cnt[i]]) % MOD;
        }
    }
    ll ans = dp[n / 2];
    ans = ans * fac[n / 2] % MOD;
    ans = ans * fac[(n + 1) / 2] % MOD;
    for(int i = 1; i <= m; i++) if(cnt[i]) ans = ans * inv_fac[cnt[i]] % MOD;
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
