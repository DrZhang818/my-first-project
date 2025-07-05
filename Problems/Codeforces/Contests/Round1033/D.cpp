#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
constexpr int inf = 1000000000;
constexpr int MOD = 1E9 + 7;

//
ll fast_pow(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    ll a, b, k;
    cin >> a >> b >> k;
    ll n, m;
    n = k * (a - 1) + 1;
    ll c = k;
    for(ll i = 1; i <= a; i++) {
        c = (n - i + 1) % MOD * c % MOD;
        c = c * fast_pow(i, MOD - 2) % MOD; 
    }
    m = (1 + c * (b - 1) % MOD) % MOD;
    cout << n % MOD << " " << m << "\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
