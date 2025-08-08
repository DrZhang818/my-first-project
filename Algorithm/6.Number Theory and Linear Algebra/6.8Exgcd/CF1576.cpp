#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 9973;

ll fast_pow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll mod(ll a, ll p) {
    return (a % p + p) % p;
}
ll mod_inv(ll a, ll p) {
    return fast_pow(a, p - 2);
}
void solve() {
    ll a, b;
    cin >> a >> b;
    cout << a * mod_inv(b, MOD) % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
