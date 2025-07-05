#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr ll MOD = 1e9 + 7;
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
void solve() { 
    ll n;
    cin >> n;
    ll ans = 0;
    ans = (n * (n + 1) % MOD * (2 * n + 1) % MOD * inv(6) % MOD) % MOD;
    n -= 1;
    ans = (ans + n * (n + 1) % MOD * (2 * n + 1) % MOD * inv(6) % MOD + n * (n + 1) % MOD * inv(2) % MOD) % MOD;
    cout << (2022 * ans % MOD) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
