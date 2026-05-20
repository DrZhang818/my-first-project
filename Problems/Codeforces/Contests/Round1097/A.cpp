#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int ans = 0;

    for(int i = n; i >= 1; i--) {
        a[i] += max(0LL, a[i + 1]);
        ans += a[i] > 0;
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