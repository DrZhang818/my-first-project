#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 200000;

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
int fac[N + 1], inv_fac[N + 1];
int C(int n, int m) {
    if(m < 0 || n < m) return 0;
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int c1 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        c1 += a[i] == 1;
    }
    int ans = 0;
    for(int i = (k + 1) / 2; i <= k; i++) {
        add(ans, 1LL * C(c1, i) * C(n - c1, k - i) % MOD);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    inv_fac[N] = inv(fac[N]);
    for(int i = N - 1; i >= 1; i--) {
        inv_fac[i] = 1LL * inv_fac[i + 1] * (i + 1) % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
