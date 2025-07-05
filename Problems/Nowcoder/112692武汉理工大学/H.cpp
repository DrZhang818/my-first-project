#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int MOD = 998244353;
ll fast_pow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
const ll inv_3 = fast_pow(3, MOD - 2);
void solve() {
    ll n;
    cin >> n;
    if(n % 2 == 0) {
        cout << (fast_pow(2, n + 1) - 2 + MOD) % MOD * inv_3 % MOD << "\n";
    } else {
        cout << (fast_pow(2, n + 1) - 1 + MOD) % MOD * inv_3 % MOD << "\n";
    }
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
