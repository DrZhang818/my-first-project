#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x, y;
    cin >> x >> y;
    if(y < x) {
        cout << "NO\n";
        return;
    }
    if((x + y) % 2 == 0 && x == 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
        
    if(x == 0) {
        for(int i = 2; i <= x + y; i++) {
            cout << 1 << " " << i << "\n";
        }
        return;
    }

    int d = y - x;
    for(int i = 1; i < x + y - d; i++) {
        cout << i << " " << i + 1 << "\n";
    }
    for(int i = x + y - d + 1; i <= x + y; i++) {
        cout << x + y - d << " " << i << "\n";
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