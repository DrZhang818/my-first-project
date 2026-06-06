#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;

    i64 ans = 0;

    int single = min(x, y);
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        int cur = 3 * single;
        if(s[0] == s[1] || s[0] == s[2] || s[1] == s[2]) {
            cur = min(cur, single + y);
        }

        ans += cur;
    }

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