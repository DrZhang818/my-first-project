#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, d, k;
    cin >> n >> d >> k;
    vector<int> a(n + 2), b(n + 2);
    for(int i = 1; i <= k; i++) {
        int l, r;
        cin >> l >> r;
        a[l]++;
        b[r]++;
    }

    int mn = inf, mx = -inf;
    int ans1 = -1, ans2 = -1;
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        cur += a[i];
        if(i < d) {
            continue;
        }
        if(cur > mx) {
            mx = cur;
            ans1 = i - d + 1;
        }
        if(cur < mn) {
            mn = cur;
            ans2 = i - d + 1;
        }
        cur -= b[i - d + 1];
    }
    cout << ans1 << " " << ans2 << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
