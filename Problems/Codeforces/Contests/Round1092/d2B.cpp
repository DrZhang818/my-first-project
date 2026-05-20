#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x, y, z;
    cin >> x >> y >> z;
    i64 ans = 3LL * (y + z);

    ans += min(x, z);
    x -= min(x, z);

    ans += 2LL * min(x, 2 * y);
    x -= min(x, 2 * y);

    if(x >= 1) {
        ans += 3 + 2LL * (x - 1);
    }

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