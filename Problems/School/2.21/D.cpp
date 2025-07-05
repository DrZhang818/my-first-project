#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll MOD = 1e9 + 7;

void solve() { 
    ll n, m;
    cin >> n >> m;
    vector<ll> x(n + 1), y(m + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];
    for (int j = 1; j <= m; j++) cin >> y[j];
    ll sum_x = 0;
    for (int i = 1; i < n; i++) {
        ll d = x[i+1] - x[i];
        sum_x = (sum_x + d % MOD * i % MOD * (n - i) % MOD) % MOD;
    }
    ll sum_y = 0;
    for (int j = 1; j < m; j++) {
        ll d = y[j+1] - y[j];
        sum_y = (sum_y + d % MOD * j % MOD * (m - j) % MOD) % MOD;
    }
    ll ans = sum_x % MOD * sum_y % MOD;
    cout << ans << "\n";    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}