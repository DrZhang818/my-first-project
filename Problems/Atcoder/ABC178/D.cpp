#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
//https://atcoder.jp/contests/abc178/tasks/abc178_d
const int MOD = 1000000007;
const int N = 2000;
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
int inv(int x) {
    return fast_pow(x, MOD - 2);
}
int fac[N + 1];
int C(int n, int m) {
    return 1LL * fac[n] * inv(fac[m]) % MOD * inv(fac[n - m]) % MOD;
}
void solve() {
    int s;
    cin >> s;
    int ans = 0;
    for(int k = 1; k * 3 <= s; k++) {
        add(ans, C(s - 2 * k - 1, k - 1));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac[0] = 1;
    for(int i = 1; i <= N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
