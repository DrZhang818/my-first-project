#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
int MOD;

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

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {  
    int n, m;
    cin >> n >> m >> MOD;
    vector<int> c(n + 1), p(n + 1);
    for(int i = 1; i <= n; i++) {
        c[i] = n - i + 1;
        p[i] = 1LL * fast_pow(m, (i + 1) / 2) * inv(fast_pow(m, i)) % MOD;
    }
    int ans = 0;
    for(int L1 = 1; L1 <= n; L1++) {
        int x = 1;
        for(int L2 = 1; L2 < L1; L2++) {
            if(L1 + L2 & 1) {
                add(x, 2LL * c[L2] * p[L2] % MOD);
            } else {
                add(x, 2LL * (c[L2] - 1) * p[L2] % MOD);
                add(x, 2);
            }
        }
        add(x, 1LL * (c[L1] - 1) * p[L1] % MOD);
        add(ans, 1LL * c[L1] * p[L1] % MOD * x % MOD);
    }
    cout << ans << "\n";

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

