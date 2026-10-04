#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, w;
    cin >> n >> w;

    array<int, 20> cnt {};
    for(int i = 1; i <= n; i++) {
        unsigned x;
        cin >> x;
        cnt[__builtin_ctz(x)]++;
    }

    int ans = 0;

    while(n > 0) {
        int rem = w;
        for(int j = 19; j >= 0; j--) {
            int len = 1 << j;
            int cur = min(cnt[j], rem / len);
            cnt[j] -= cur;
            n -= cur;
            rem -= cur * len;
        }
        ans++;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}