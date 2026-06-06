#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    auto ck = [&](int a, int b, int c, int d) {
        return x1 == a && y1 == b && x2 == c && y2 == d;
    };

    if(ck(2, 2, 4, 4) || ck(8, 2, 6, 4) || ck(2, 9, 4, 7) || ck(8, 9, 6, 7) || ck(2, 1, 4, 3) || ck(2, 10, 4, 8) || ck(1, 2, 3, 4) || ck(1, 9, 3, 7) || ck(8, 1, 6, 3) || ck(9, 2, 7, 4) || ck(8, 10, 6, 8) || ck(9, 9, 7, 7)) {
        cout << "YES\n";
        return;
    }

    if(x1 == 1 || y1 == 1 || x1 == 9 || y1 == 10) {
        if(x1 == 1 && x2 == 2 && y1 == y2 || x1 == 9 && x2 == 8 && y1 == y2 || y1 == 1 && y2 == 2 && x1 == x2 || y1 == 10 && y2 == 9 && x1 == x2) {
            cout << "YES\n";
        } else if(x1 == 1 && y1 == 1 && (x2 == 2 && y2 == 2 || x2 == 3 && y2 == 3) 
                || x1 == 9 && y1 == 1 && (x2 == 8 && y2 == 2 || x2 == 7 && y2 == 3)
                || x1 == 1 && y1 == 10 && (x2 == 2 && y2 == 9 || x2 == 3 && y2 == 8)
                || x1 == 9 && y1 == 10 && (x2 == 8 && y2 == 9 || x2 == 7 && y2 == 8)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else {
        cout << "NO\n";
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