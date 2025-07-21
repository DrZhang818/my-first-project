#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

PII dir[8] = {{-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}};
void solve() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    n++, m++, x++, y++;
    vector dp(n + 1, vector<ll>(m + 1));
    vector vis(n + 1, vector<bool>(m + 1));
    if(x >= 1 && x <= n && y >= 1 && y <= m) vis[x][y] = true;
    for(int i = 0; i < 8; i++) {
        int nx = x + dir[i].first, ny = y + dir[i].second;
        if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
        vis[nx][ny] = true;
    }
    if(vis[1][1]) {
        cout << 0 << "\n";
        return;
    }
    dp[1][1] = 1; 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(vis[i][j] || i == 1 && j == 1) continue;
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    cout << dp[n][m] << "\n";
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
