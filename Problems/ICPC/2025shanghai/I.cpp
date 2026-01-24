#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);
constexpr int high_mask = 1 << 9;

void solve() {  
    int n, C;
    cin >> n >> C;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> f(1 << 18, inf), g(1 << 18, inf);
    f[0] = 0;
    for(int i = 0; i <= n + 1; i++) {
        for(int j = 0; j < high_mask; j++) {
            f[i] = min(f[i], g[a[i] ^ (j << 9)] + (j << 9) + 1LL * i * C);
        }
        for(int j = 0; j < high_mask; j++) {
            g[a[i] ^ j] = min(g[a[i] ^ j], f[i] + j - 1LL * (i + 1) * C);
        }
    }
    cout << f[n + 1] << "\n";
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
