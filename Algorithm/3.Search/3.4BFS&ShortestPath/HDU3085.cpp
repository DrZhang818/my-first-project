#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int x, y;
};
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    info B, G, Z[2];
    int idx = 0;
    auto check = [&](int x, int y, int t) {
        if(x < 1 || x > n || y < 1 || y > m || a[x][y] == 'X') return false;
        for(int i = 0; i < 2; i++) {
            if(abs(Z[i].x - x) + abs(Z[i].y - y) <= 2 * t) {
                return false;
            }
        }
        return true;
    };
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 'M') B = {i, j};
            else if(a[i][j] == 'G') G = {i, j};
            else if(a[i][j] == 'Z') Z[idx++] = {i, j};
        }
    }
    int dir[5] = {-1, 0, 1, 0, -1};
    queue<info> qb, qg;
    qb.push(B);
    qg.push(G);
    vector<vector<int>> vis(n + 1, vector<int>(m + 1));
    vis[B.x][B.y] = 1, vis[G.x][G.y] = 2;
    int tim = 0;
    while(!qb.empty() || !qg.empty()) {
        tim++;
        for(int i = 0; i < 3; i++) {
            int sz = qb.size();
            while(sz--) {
                auto [x, y] = qb.front(); qb.pop();
                if(!check(x, y, tim)) continue;
                for(int k = 0; k < 4; k++) {
                    int nx = x + dir[k], ny = y + dir[k + 1];
                    if(check(nx, ny, tim)) {
                        if(vis[nx][ny] == 2) {
                            cout << tim << "\n";
                            return;
                        } else if(!vis[nx][ny]) {
                            vis[nx][ny] = 1;
                            qb.push({nx, ny});
                        }
                    }
                }
            }
        }
        int sz = qg.size();
        while(sz--) {
            auto [x, y] = qg.front(); qg.pop();
            if(!check(x, y, tim)) continue;
            for(int k = 0; k < 4; k++) {
                int nx = x + dir[k], ny = y + dir[k + 1];
                if(check(nx, ny, tim)) {
                    if(vis[nx][ny] == 1) {
                        cout << tim << "\n";
                        return;
                    } else if(!vis[nx][ny]) {
                        vis[nx][ny] = 2;
                        qg.push({nx, ny});
                    }
                }
            }
        }
    }
    cout << -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
