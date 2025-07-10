#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {0, 1, 0, -1, 0};
struct info {
    int x, y;
};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n + 1, vector<int>(m + 1, inf));
    queue<info> q;        
    for(int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 0;
        q.push({x, y});
    }
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] != inf) continue;
            int c = 0;
            for(int j = 0; j < 4; j++) {
                int mx = nx + dir[j], my = ny + dir[j + 1];
                if(mx < 1 || mx > n || my < 1 || my > m || a[mx][my] > a[x][y]) continue;
                c++;
            }
            if(c >= 2) {
                a[nx][ny] = a[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != inf) {
                ans += a[i][j];
            }
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
