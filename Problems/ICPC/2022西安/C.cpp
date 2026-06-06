#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    i64 a, b, c;
    cin >> a >> b >> c;

    i64 ans = 1LL * b * c;
    for(i64 x = 1, time = 0; ; x <<= 1) {
        ans = min(ans, (c + x - 1) / x * b + time);
        time += a;
        if(x >= c) break;
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