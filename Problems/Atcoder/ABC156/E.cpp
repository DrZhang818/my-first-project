#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://atcoder.jp/contests/abc156/tasks/abc156_e
/*
    

*/
ll fac[200005], inv_fac[200005];
ll pow_mod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll C(int n, int m) {
    if(n < m) return 0;
    return fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}
void solve() {
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    int up = min(k, n - 1);
    for(int i = 0; i <= up; i++) {
        ans = (ans + C(n, i) * C(n - 1, n - i - 1) % MOD) % MOD;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1, inv_fac[0] = 1;
    for(int i = 1; i <= 200000; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        inv_fac[i] = pow_mod(fac[i], MOD - 2);
    }
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
