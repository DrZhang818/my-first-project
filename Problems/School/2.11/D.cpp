#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


const int MOD = 1e9 + 7;
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
    int n, k;
    cin >> n >> k;
    int lo = 1, hi = k;
    for(int i = lo; i <= hi; i++) {
        ll ans = 0;
        int gap = i - 1;
        if(gap == 0) {
            ans = (ans + n - k + 1) % MOD;
        } else {
            for(int i = gap; i <= n - k; i++)
            ans = (ans + (n - k - i + 1) * (nCr(k - 1, gap)) % MOD * nCr(i - 1, gap - 1)) % MOD;
        }
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

