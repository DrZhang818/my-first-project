#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

int fast_pow(ll a, int b) {
    a %= MOD;
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv[21];
int C(ll n, int m) {
    if(m == 0) return 1;
    int res = 1;
    for(int i = m; i >= 1; i--) {
        res = 1LL * (n - (m - i)) % MOD * res % MOD;
        res = 1LL * res * inv[i] % MOD;
    }
    return res;
}
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n;
    ll s;
    cin >> n >> s;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> g(n + 1);
    for(int i = 0; i < 1 << n; i++) {
        g[__builtin_popcount(i)].push_back(i);
    }
    int ans = 0;
    for(int i = 0, tag = 1; i <= n; i++, tag ^= 1) {
        int cur = 0;
        for(int j : g[i]) {
            ll tot = s;
            for(int k = 0; k < n; k++) {
                if(j >> k & 1) {
                    tot -= a[k] + 1;
                }
            }
            if(tot < 0) {
                continue;
            }
            add(cur, C(tot + n - 1, n - 1));
        }
        if(tag) {
            add(ans, cur);
        } else {
            add(ans, MOD - cur);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= 20; i++) {
        inv[i] = fast_pow(i, MOD - 2);
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
