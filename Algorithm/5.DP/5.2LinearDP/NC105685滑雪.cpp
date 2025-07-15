#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {-1, 0, 1, 0, -1};
void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector dp(n + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int x, int y) -> int {
        int &res = dp[x][y];
        if(res) return res;
        res = 1;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || a[x][y] <= a[nx][ny]) continue;
            res = max(res, self(self, nx, ny) + 1);
        }
        return res;
    };
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(dp[i][j] == 0) {
                ans = max(ans, dfs(dfs, i, j));                
            }
        }
    }
    cout << ans << "\n";
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
