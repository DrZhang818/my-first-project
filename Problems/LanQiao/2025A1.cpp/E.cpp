#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
ll pow_mod(ll a, ll b) {
    a = a % MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
inline ll inv(ll x) { return pow_mod(x, MOD - 2); }
void solve() {
    int n;
    cin >> n;
    vector<ll> a(500005), fac(n + 1, 1);
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[x]++;
    }    
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    n -= 2;
    ll ans = 0, tot = 1;
    for(int i = 1; i <= 500000; i++) {
        tot = tot * fac[a[i]] % MOD;
    }
    ll inv_tot = inv(tot), num = fac[n] * inv_tot % MOD;
    for(int i = 1; i <= n; i++) {
        if(n % i == 0 && a[i] && a[n / i]) {
            ll cur = num;
            if(i * i == n) cur = cur * a[i] % MOD * (a[i] - 1) % MOD;
            else cur = cur * a[i] % MOD * a[n / i] % MOD;
            ans = (ans + cur) % MOD;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
