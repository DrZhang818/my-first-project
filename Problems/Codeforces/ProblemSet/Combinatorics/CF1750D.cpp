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

int mod(int x) {
    return ((x % MOD) + MOD) % MOD;
}

int cal(int n, int x) {
    vector<PII> pe;
    for(int p = 2; p * p <= x; p++) {
        if(x % p == 0) {
            pe.emplace_back(p, 1);
            while(x % p == 0) {
                x /= p;
            }
        }
    }
    if(x > 1) {
        pe.emplace_back(x, 1);
    }
    int res = 0;
    int sz = pe.size();
    auto dfs = [&](this auto &&self, int i, int fac, int sume) {
        if(i == sz) {
            if(sume & 1) {
                add(res, mod(-(n / fac)));
            } else {
                add(res, mod(n / fac));
            }
            return;
        }
        auto [P, E] = pe[i];
        for(int e = 0, p = 1; e <= E; e++, p *= P) {
            self(i + 1, fac * p, sume + e);
        }
    };
    dfs(0, 1, 0);
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 1;
    for(int i = 2; i <= n; i++) {
        if(a[i - 1] % a[i] != 0) {
            cout << 0 << "\n";
            return;
        }
        int x = a[i - 1], y = a[i];
        int up = m / y, p = x / y;
        ans = 1LL * ans * cal(up, p) % MOD;
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
