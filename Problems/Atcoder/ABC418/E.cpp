#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ldb;
typedef pair<ll,ll> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    ll x, y;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }
    unordered_map<ldb, int> mp1;
    unordered_map<ll, int> mp2;
    for(int i = 1; i <= n; i++) {
        auto [x1, y1] = a[i];
        for(int j = i + 1; j <= n; j++) {
            auto [x2, y2] = a[j];
            ll dx = x2 - x1, dy = y2 - y1;
            ldb k = dx ? 1.0 * dy / dx : DBL_MAX;
            mp1[k]++;
            ll mid = (x1 + x2) << 32 | (y1 + y2);
            mp2[mid]++;
        }
    }
    ll ans = 0;
    for(auto &[k, cnt] : mp1) {
        ans += 1LL * cnt * (cnt - 1) / 2;
    }
    for(auto &[mid, cnt] : mp2) {
        ans -= 1LL * cnt * (cnt - 1) / 2;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
