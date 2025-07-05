#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1e9 + 7;
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
    ll n, a, b;
    cin >> n >> a >> b;
    ll tot = fast_pow(2, n);
    tot = (tot - 1 + MOD) % MOD;
    ll t1 = 1, t2 = 1;
    for(int i = 1; i <= a; i++) {
        t1 = t1 * (n - a + i) % MOD * fast_pow(i, MOD - 2) % MOD;
    }   
    for(int i = 1; i <= b; i++) {
        t2 = t2 * (n - b + i) % MOD * fast_pow(i, MOD - 2) % MOD;
    }
    tot = (tot - t1 + MOD) % MOD;
    tot = (tot - t2 + MOD) % MOD;
    cout << tot << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
