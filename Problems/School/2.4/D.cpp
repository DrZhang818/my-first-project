#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



const int MOD = 1e9 + 7;
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
const int MX = 1e6;
ll binpow(ll a, ll b, ll m = MOD){
    ll res = 1;
    a %= m;
    while(b > 0){
        if(b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

inline ll inv(ll a){
    return binpow(a, MOD - 2, MOD);
}

static ll fact[MX + 1], invfact[MX + 1];
void init_factorials(){
    fact[0] = 1;
    for(int i = 1; i <= MX; i++){
        fact[i] = fact[i - 1] * i % MOD;
    }
    invfact[MX] = inv(fact[MX]);
    for(int i = MX - 1; i >= 0; i--){
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
    }
}

ll nCr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

ll nPr(int n, int r){
    if(r > n || r < 0) return 0;
    return fact[n] * invfact[n - r] % MOD;
}
void solve(){
    init_factorials();
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    ll ans = 0;
    if(a * b == 0) {
        int s = n + m - 2;
        ans = nCr(s, min(n - 1, m - 1));
        cout << ans << "\n";
        return;
    }
    for(int i = 1; i <= n - a; i++){
        int step1 = i + b - 2;
        int step2 = n - i + 1 + m - b - 2;
        ans = (ans + nCr(step1, min(i - 1, b - 1)) * nCr(step2, min(n - i, m - b - 1)) % MOD) % MOD;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

