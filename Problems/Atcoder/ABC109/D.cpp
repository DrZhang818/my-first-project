#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y, nx, ny;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector<info> ans;
    for(int i = 1; i <= n; i++) {
        if(i >= 2) {
            if(a[i - 1][m] & 1) {
                ans.emplace_back(i - 1, m, i, m);
                a[i - 1][m] -= 1;
                a[i][m] += 1;
            }
        }
        for(int j = 2; j <= m; j++) {
            if(a[i][j - 1] & 1) {
                ans.emplace_back(i, j - 1, i, j);
                a[i][j - 1] -= 1;
                a[i][j] += 1;
            }
        }
    }
    cout << ans.size() << "\n";
    for(auto [x, y, nx, ny] : ans) {
        cout << x << " " << y << " " << nx << " " << ny << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
