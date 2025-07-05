#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int MOD = 998244353;
const int MAX = 1e6 + 5;

//https://citel.bjtu.edu.cn/acm/problem/1960
/*
    动态规划(背包 TLE) -> 数学算法(组合)
    核心思想：
            我们发现监控计划的选择可以视为从所有组织中独立选择任意子集的人进行监控。
            每个智子对应一个独立的集合，选择监控的人数相当于从该集合中选择一个子集。
            监控计划的总监控人数不超过𝑝。
    因此结果就是Answer= ∑ C[S][t] mod 998244353 (t in range[1, p])
    其中S = ∑a_i (i in range [1, k])
    
*/

// 预计算阶乘和逆阶乘
vector<long long> fact(MAX, 1);
vector<long long> inv_fact(MAX, 1);

// 快速幂计算 a^b % MOD
ll power_pow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// 预计算阶乘和逆阶乘
void precompute(){
    for(int i = 1; i < MAX; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    inv_fact[MAX - 1] = power_pow(fact[MAX - 1], MOD - 2, MOD);
    for(int i = MAX - 2; i >= 0; i--){
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

// 计算组合数 C(n, m) % MOD
inline ll comb(int n, int m){
    if(m < 0 || m > n) return 0;
    return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
}


//动态规划(超时)
void solve1(){   
    int k, LIM;
    cin >> k;
    vector<int> count(k);
    int maxNum = 0;
    for (int i = 0; i < k; ++i){
        cin >> count[i];
        maxNum = max(maxNum, count[i]);
    }
    cin >> LIM;
    vector<int> dp(LIM + 1, 0);
    dp[0] = 1;

    for(int i = 0; i < k; i++){
        int n = count[i];
        for(int j = LIM; j >= 1; j--){
            for(int m = 1; m <= min(n, j); m++){
                dp[j] = (dp[j] + (ll)dp[j - m] * comb(n, m) % MOD) % MOD;
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i <= LIM; i++){
        ans = (ans + dp[i]) % MOD;
    }
    cout << ans << "\n"; 
}
//正解: 组合数学
void solve2(){   
    int k;
    cin >> k;
    vector<int> count(k);
    ll S = 0;
    for(int i = 0; i < k; i++){
        cin >> count[i];
        S += count[i];
    }
    int p;
    cin >> p;
    
    ll ans = 0;
    for(int t = 1; t <= p; t++){
        ans = (ans + comb(S, t)) % MOD;
    }
    cout << ans << "\n"; 
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    precompute(); // 预计算阶乘和逆阶乘
    solve();
    return 0;
}
