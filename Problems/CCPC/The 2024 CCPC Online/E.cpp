#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

int fast_pow(int a, ll b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

int inv(int x) {
    return fast_pow(x, MOD - 2);
}

void solve() {
    int n, m;
    cin >> n >> m;


    int ans1 = 1;
    ll sz = 26;
    bool tag = false;
    for(int i = 1; i <= m; i++) {
        if(!tag) {
            add(ans1, min((ll)n, sz));
            sz = 26 * sz;
            if(sz > n) {
                tag = true;
            }
        } else {
            add(ans1, n);
        }
    }
    cout << ans1 << " ";

    int inv26nm = inv(fast_pow(26, 1LL * n * m));
    int ans = 1;
    for(int i = 1; i <= m; i++) {
        int t = fast_pow(26, i);
        int p = (1 - 1LL * fast_pow(t - 1, n) * fast_pow(26, 1LL * n * (m - i)) % MOD * inv26nm % MOD + MOD) % MOD;
        add(ans, 1LL * p * t % MOD);
    }
    cout << ans << "\n";
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
