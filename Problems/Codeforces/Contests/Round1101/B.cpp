#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    i64 x = a[1], w = 0;
    for(int i = 1; i <= n; i++) {
        i64 y = a[i];
        i64 ans = x;
        if(y >= x) {
            w += y - x;
        } else {
            ans = min(x, (w + x * (i - 1) + y) / i);
            w += (x - ans) * (i - 1) + y - ans;
        }
        x = ans;
        cout << ans << " \n"[i == n];
    }
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