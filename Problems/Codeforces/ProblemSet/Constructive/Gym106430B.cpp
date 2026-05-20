#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    i64 X, Y;
    cin >> X >> Y;

    if(X == Y) {
        cout << 0 << "\n";
        return;
    }

    int ans = 0;
    if(X < Y) {
        while(X < Y) {
            ans++;
            X = min(Y, X << 1);
        }
    } else {
        if(Y <= 2) {
            cout << -1 << "\n";
            return;
        }
        while(X > Y) {
            ans++;
            X = max(Y, (2 * X + 3) / 3);
        }
    }

    cout << ans << "\n";
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
