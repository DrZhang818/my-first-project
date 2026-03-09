#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    if(min(n, m) + 1 < max(n, m)) {
        cout << -1 << "\n";
        return;
    }

    vector<vector<int>> a(n, vector<int>(m));

    int s = (n < m);

    int x = 0, y = 0;
    while(x < n && y < m) {
        a[x][y] = 1;
        if(s) {
            y++;
        } else {
            x++;
        }
        s ^= 1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << a[i][j];
        }
        cout << "\n";
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
