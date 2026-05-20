#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 2E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<i64> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    auto ck = [&](i64  x) {
        i64 need = 0;
        for(int i = 1; i <= n; i++) {
            need += max(0LL, a[i] - x);
        }
        return need <= k;
    };

    i64 lo = -1, hi = inf + 1;
    while(lo + 1 < hi) {
        i64 mid = lo + (hi - lo) / 2;
        if(ck(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    } 

    i64 ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] < hi) continue;
        ans += (a[i] + hi + 1) * (a[i] - hi) / 2;
        k -= a[i] - hi;
        a[i] = hi;
    }
    ans += k * hi;
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
