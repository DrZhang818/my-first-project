#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n;
    cin >> n;
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector a(n + 1, vector<char>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    vector vis(n + 1, vector<bool>(n + 1, false));
    int ans = 0;
    bool ok = false;
    function<void(int,int)> dfs = [&](int x, int y) -> void {
        vis[x][y] = true;
        if(a[x + 1][y] == '#' && a[x][y + 1] == '#' && a[x - 1][y] == '#' && a[x][y - 1] == '#') {
            ok = true;
        }
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];
            if(!vis[nx][ny] && a[nx][ny] == '#') {
                dfs(nx, ny);
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!vis[i][j] && a[i][j] == '#') {
                ok = false;
                dfs(i, j);
                if(!ok) {
                    ans += 1;
                }
            }
        }
    }
    cout << ans << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

