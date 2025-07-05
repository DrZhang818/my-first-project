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
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    bool have = false;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 'G') have = true;
        }
    }
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == 'B') {
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == 'B') continue;
                    if(a[nx][ny] == 'G' || nx == n && ny == m && have) ok = false;
                    a[nx][ny] = '#';
                }
            }
        }
    }
    if(!ok) {
        cout << "No\n";
        return ;
    }
    queue<PII> q;
    q.push({n, m});
    vector<vector<int>> vis(n + 1, vector<int>(m + 1));
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        vis[x][y] = true;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#' || vis[nx][ny]) continue;
            vis[nx][ny] = true;
            q.push({nx, ny});
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == 'G' && !vis[i][j]) {
                cout << "No\n";
                return;
            }
        }
    }
    cout << "Yes\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    