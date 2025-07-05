#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


const int MOD = 1e9 + 7;
const int MX = 1e6;
//带模快速幂
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
    ll n, x, y, z;
    cin >> n >> x >> y >> z;
    ll sum = x + y + z;
    vector<vector<ll>> a(10, vector<ll>(10));
    auto f = [&](ll num) -> void {
        for(int i = 1; i <= num; i++) { 
            a[num][i] = nCr(num - 1, i - 1);
        }
    };
    f(x), f(y), f(z);
    ll ans = 0;
    for(int len = 3; len <= min(sum, n); len++) {
        for(int i = 1; i <= x; i++) {
            for(int j = 1; j <= y; j++) {
                for(int k = 1; k <= z; k++) {
                    if(i + j + k > len) break;
                    if(i + j + k == len){
                        ans = (ans + (n - len + 1) * a[x][i] * a[y][j] * a[z][k] % MOD * power_pow(10, n - len) % MOD) % MOD;
                        break;
                    }
                }
            }
        }
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

