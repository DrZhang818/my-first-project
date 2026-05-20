#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr int MOD = 676767677;

void solve() {
    int n;
    cin >> n;

    int ans = 0, vis = 0, las = -1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == 1) {
            vis = 1;
        } else {
            ans += x;
        }
        las = x;
    }

    if(vis) {
        if(las == 1) ans++;
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