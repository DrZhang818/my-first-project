#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, x;
    cin >> n >> x;
    for(int i = 1; i <= n; i++) {
        int y;
        cin >> y;
        if(y < x) {
            x = y;
            cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
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
