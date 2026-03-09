#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    i64 x, y;
    cin >> x >> y;

    i64 tx = 0;
    if(y > 0) {
        tx += 2 * y;
    } else {
        tx += 4 * abs(y);
    }
    if(tx > x || (x - tx) % 3 != 0) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
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
