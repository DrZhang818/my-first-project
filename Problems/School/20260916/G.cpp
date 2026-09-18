#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    int n, k, x;
    cin >> n >> k >> x;
    if(n < k || x < k - 1) {
        cout << -1 << "\n";
        return;
    }
    i64 ans = k * (k - 1) / 2;
    if(x == k) x--;
    ans += (n - k) * x;
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