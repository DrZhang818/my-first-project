#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 19260817;

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
    string s, t;
    cin >> s >> t;
    ll a = 0, b = 0;
    for(char c : s) {
        int x = c - '0';
        a = mod(a * 10 + x, MOD);
    }
    for(char c : t) {
        int x = c - '0';
        b = mod(b * 10 + x, MOD);
    }
    cout << a * mod_inv(b, MOD) % MOD << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
