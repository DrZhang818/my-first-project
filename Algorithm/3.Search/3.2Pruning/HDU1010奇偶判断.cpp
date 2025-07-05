#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://acm.hdu.edu.cn/showproblem.php?pid=1010
void solve(int n, int m, int t){ 
    vector<vector<char>> a(n, vector<char>(m));
    int sx, sy, ex, ey;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 'S') {
                sx = i;
                sy = j;
            } else if(a[i][j] == 'D') {
                ex = i;
                ey = j;
            }
        }
    }
    int D = abs(sx - ex) + abs(sy - ey);
    if(t < D || (t & 1) != (D & 1)) {
        cout << "NO\n"; 
        return;
    }
    bool ok = false;
    int dir[5] = {-1, 0, 1, 0, -1};
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vis[sx][sy] = true;
    auto dfs = [&](auto &&dfs, int x, int y, int cnt) {
        if(ok) return ;
        if(x == ex && y == ey && cnt == t) {
            ok = true;
            return;
        }  
        if(cnt >= t) {
            return;
        }
        for(int i = 0; i < 4 && !ok; i++) {
            int nx = x + dir[i];
            int ny = y + dir[i + 1];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == 'X' || vis[nx][ny]) {
                continue;
            }
            vis[nx][ny] = true;
            dfs(dfs, nx, ny, cnt + 1);
            vis[nx][ny] = false;
        }
    };
    dfs(dfs, sx, sy, 0);
    if(ok) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, t;
    while(cin >> n >> m >> t && n) {
        solve(n, m, t);
    }
    return 0;
}
    
