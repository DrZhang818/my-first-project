#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 998244353;

i64 calc(i64 n, int m) {
    if(n < m) return 0;
    return (n - m) / 4 + 1;
}

void solve() {
    i64 n, x;
    cin >> n >> x;
    i64 ans = 0;
    ans = (ans + (calc(n, 1) - calc(x - 1, 1)) % MOD * (calc(x - 1, 1) % MOD)) % MOD;
    ans = (ans + (calc(n, 3) - calc(x - 1, 3)) % MOD * ((calc(x - 1, 3) + 1) % MOD)) % MOD;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}