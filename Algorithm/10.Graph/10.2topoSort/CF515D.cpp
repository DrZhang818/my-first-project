#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {-1, 0, 1, 0, -1};
struct info {
    int x, y;
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 2, vector<char>(m + 2, '*'));
    vector<vector<char>> ch = {{'v','^'},{'<','>'},{'^','v'},{'>','<'}};
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }    
    auto cal = [&](int x, int y) {
        if(x < 1 || x > n || y < 1 || y > m) return -1;
        int res = 0;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            res += a[nx][ny] == '.';
        }
        return res;
    };
    queue<info> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == '.' && cal(i, j) == 1) {
                q.push({i, j});
            }
        }
    }
    bool ok = true;
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        int nx, ny;
        for(int i = 0; i < 4; i++) {
            nx = x + dir[i], ny = y + dir[i + 1];
            if(a[nx][ny] == '.') {
                a[x][y] = ch[i][0];
                a[nx][ny] = ch[i][1];
                break;
            }
        }
        for(int i = 0; i < 4; i++) {
            int tx = x + dir[i], ty = y + dir[i + 1], sz;
            sz = cal(tx, ty);
            if(a[tx][ty] == '.') {
                if(sz == 1) q.push({tx, ty});
                else if(sz == 0) ok = false;
            }
            tx = nx + dir[i], ty = ny + dir[i + 1];
            sz = cal(tx, ty);
            if(a[tx][ty] == '.') {
                if(sz == 1) q.push({tx, ty});
                else if(sz == 0) ok = false;
            }
        }
        if(!ok) break;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == '.') ok = false;
        }
    }
    if(!ok) {
        cout << "Not unique\n";
        return ;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout << a[i][j];
        }
        cout << "\n";
    }
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
