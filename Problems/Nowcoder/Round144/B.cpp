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
    if(n == 1) {
        cout << 1 << "\n";
    } else if(n == 2) {
        cout << 1 << " " << 2 << "\n" << 3 << " " << 4 << "\n";
    } else if(n == 3) {
        cout << "1 2 3\n5 4 6\n7 8 9\n";
    } else {
        cout << -1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}