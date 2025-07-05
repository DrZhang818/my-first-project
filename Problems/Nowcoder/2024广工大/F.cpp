#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

const int MOD = 1e9 + 7;
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
const int MAX = 1e5 + 5;
std::vector<ll> fact(MAX, 1);
std::vector<ll> inv_fact(MAX, 1);
void precompute(){
    for(int i = 1; i < MAX; i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    inv_fact[MAX - 1] = power_pow(fact[MAX - 1], MOD - 2, MOD);
    for(int i = MAX - 2; i >= 0; i--){
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}
inline ll A(int n, int m){
    if(m < 0 || m > n) return 0;
    return fact[n] * inv_fact[n - m] % MOD;
}
void solve(){
    int n;
    cin >> n;
    int temp = n;
    while(temp--){
        string s;
        cin >> s;
    }
    
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        ans = (ans + A(n, i)) % MOD;
    }
    cout << ans << "\n";
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    precompute();
    solve();
    return 0;
}
