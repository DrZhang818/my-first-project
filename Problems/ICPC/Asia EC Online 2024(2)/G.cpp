#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

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

int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

void solve() {
    int x, y;
    cin >> x >> y;
    int a0, a1, b;
    cin >> a0 >> a1 >> b;

    int win = 1LL * a0 * inv(a0 + a1) % MOD;
    int lose = 1LL * a1 * inv(a0 + a1) % MOD;

    auto dfs = [&](this auto &&self, int x, int y) -> int {
        if(x == y) {
            return win;
        } else if(x > y) {
            int t = (x + y - 1) / y - 1;
            int np = self(x - y * t, y);
            int lose_t = fast_pow(lose, t);
            return (1LL * win * mod(1 - lose_t) % MOD * inv(mod(1 - lose)) % MOD + 1LL * lose_t * np % MOD) % MOD;
        } else {
            int t = (y + x - 1) / x - 1;
            int np = self(x, y - x * t);
            int win_t = fast_pow(win, t);
            return 1LL * win_t * np % MOD;
        }
    };
    cout << dfs(x, y) << "\n";
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
