#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x, y;
    cin >> x >> y;
    cout << 2 * (x - y) << "\n";
    for(int i = y; i <= x; i++) {
        cout << i << " ";
    }
    for(int i = x - 1; i > y; i--) {
        cout << i << " ";
    }
    cout << "\n";
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