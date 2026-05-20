#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

int query(int i, int j) {
    cout << "? " << i << " " << j << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int x) {
    cout << "! " << x << endl;
}

void solve() {
    int n;
    cin >> n;
    for(int i = 1; i <= 2 * n - 2; i += 2) {
        if(query(i, i + 1)) {
            answer(i);
            return;
        }
    }

    int x = query(2 * n - 1, 1);
    int y = query(2 * n - 1, 2);

    if(x || y) {
        answer(2 * n - 1);
    } else {
        answer(2 * n);
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
