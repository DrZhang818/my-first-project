#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

const ll MOD = 1e9 + 7;

ll power_pow(ll a, ll b){
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll count_inv(ll a, ll b){
    return a * power_pow(b, MOD - 2) % MOD;
}
const int MAX = 2e5 + 5;
vector<ll> fact(MAX, 1);
vector<ll> inv_fact(MAX, 1);
void precompute(){
    for(int i = 1; i < MAX; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    inv_fact[MAX - 1] = power_pow(fact[MAX - 1], MOD - 2);
    for(int i = MAX - 2; i >= 0; i--){
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

inline ll comb(int n, int m){
    if(m < 0 || m > n) return 0;
    return fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD;
}

void solve(){
    int n, p, q;
    cin >> n >> p >> q;
    ll yes = count_inv(p, q);
    ll no = count_inv(q - p, q);
    
    ll base = power_pow(yes, n);
    ll ans = 0;
   
    for(int i = 0; i <= n - 1; i++){
        ans = (ans + base * comb(n + i - 1, i) % MOD * power_pow(no, i) % MOD) % MOD;
    }

    cout << ans << "\n";
}


int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    precompute();
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}