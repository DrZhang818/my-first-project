#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int l, r, k;
    cin >> l >> r >> k;

    int n = r - l + 1;
    int q = n / k;
    int rem = n % k;
    
    i64 ans = 1LL * (q + 1) * q / 2 * rem + 1LL * q * (q - 1) / 2 * (k - rem);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}