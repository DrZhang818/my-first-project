#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int x, y;
    cin >> x >> y;
    int d = abs(x - y);
    int ans = 0;
    for(int i = 1; i * i <= d; i++) {
        if(d % i == 0) {
            ans++;
            if(i * i != d) {
                ans++;
            }
        }
    }
    if(d == 0) {
        ans = 1;
    }
    cout << ans << "\n";
    for(int i = 0; i < x; i++) {
        cout << 1 << " ";
    }
    for(int i = 0; i < y; i++) {
        cout << -1 << " ";
    }
    cout << "\n";
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
