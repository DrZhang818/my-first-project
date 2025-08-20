#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {-1, 0, 1, 0, -1};
char to[4];
struct info {
    int x, y;
};
void solve(){
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    vector vis(n + 1, vector<int>(m + 1));
    queue<info> q;
    for(int i = 1; i <= n; i++) {
        if(a[i][1] == 'L') {
            q.push({i, 1});
        }
        if(a[i][m] == 'R') {
            q.push({i, m});
        }
    }
    for(int j = 1; j <= m; j++) {
        if(a[1][j] == 'U') {
            q.push({1, j});
        }
        if(a[n][j] == 'D') {
            q.push({n, j});
        }
    }
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        vis[x][y] = true;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] != to[i] || vis[nx][ny]) continue;
            q.push({nx, ny});             
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != '?' && !vis[i][j]) {
                ans++;
            }
            if(a[i][j] == '?') {
                bool ok = false;
                for(int k = 0; k < 4; k++) {
                    int nx = i + dir[k], ny = j + dir[k + 1];
                    if(nx < 1 || nx > n || ny < 1 || ny > m || vis[nx][ny]) continue;
                    ok = true;
                }
                if(ok) {
                    ans++;
                }
            }            
        }
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    to[0] = 'D';
    to[1] = 'L';
    to[2] = 'U';
    to[3] = 'R';
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
