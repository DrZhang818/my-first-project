#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


struct node {
    int x, y;
};
void print(int x, int y, vector<vector<char>> &pre) {
    if(x == 0 && y == 0) {
        return;
    }
    if(pre[x][y] == 'D') print(x - 1, y, pre);
    if(pre[x][y] == 'L') print(x, y + 1, pre);
    if(pre[x][y] == 'R') print(x, y - 1, pre);
    if(pre[x][y] == 'U') print(x + 1, y, pre);
    cout << pre[x][y];
}
void solve(){ 
    int n = 30, m = 50;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }    
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1, false));
    queue<node> q;
    vector<vector<char>> pre(n + 1, vector<char>(m + 1));
    char k[4] = {'D', 'L', 'R', 'U'};
    int dir[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
    vis[0][0] = true;
    q.push({0,0});
    while(!q.empty()) {
        auto cur = q.front();
        q.pop();
        if(cur.x == n - 1 && cur.y == m - 1) {
            print(n - 1, m - 1, pre);
            return;
        }
        for(int i = 0; i < 4; i++) {
            int nx, ny;
            nx = cur.x + dir[i][0];
            ny = cur.y + dir[i][1];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if(vis[nx][ny] || a[nx][ny] == '1') {
                continue;
            }
            q.push({nx, ny});
            vis[nx][ny] = true;
            pre[nx][ny] = k[i];
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

