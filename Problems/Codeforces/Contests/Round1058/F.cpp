#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = int(1E6);
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
int fac[N + 1], inv_fac[N + 1];

int C(int n, int m) {
    if(n < m) {
        return 0;
    }
    return 1LL * fac[n] * inv_fac[m] % MOD * inv_fac[n - m] % MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 0; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] > n) {
            cout << 0 << "\n";
            return;
        }
        if(a[i] > 0 && a[a[i]] == -1) {
            a[a[i]] = i;
        }
        if(a[i] > 0 && a[a[i]] != i) {
            cout << 0 << "\n";
            return;
        }
    }

    int tot = 0;
    for(int i = 1; i <= n; i++) {
        tot += a[i] == -1;
    }

    vector<int> dp(n + 1);
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1];
        add(dp[i], 1LL * (i - 1) * dp[i - 2] % MOD);
    }

    int ans = 0;
    for(int i = 0; i <= tot; i++) {
        int m = tot - (a[n] == -1);
        add(ans, 1LL * C(m, i) * dp[tot - i] % MOD);
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
    inv_fac[N] = fast_pow(fac[N], MOD - 2);
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
