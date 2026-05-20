#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;

    int x = inf + 1, y = -inf;
    int cx = 0, cy = 0;
    for(int i = 1; i <= n; i++) {
        int val;
        cin >> val;

        if(val == x) {
            cx++;
        } else if(val < x) {
            tie(x, cx) = pair{val, 1};
        }

        if(val == y) {
            cy++;
        } else if(val > y) {
            tie(y, cy) = pair{val, 1};
        }


        if(cx == 1 && cx + cy == i) {
            cout << 2 * y << " \n"[i == n];
        } else {
            cout << x + y << " \n"[i == n];
        }
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