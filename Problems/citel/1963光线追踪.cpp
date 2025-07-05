#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int dir[4] = {1, 0, 3, 2};
int rdir[4] = {3, 2, 1, 0};

void solve(){
    int n, m, x, y, d;
    cin >> n >> m >> x >> y >> d;
    x--;
    y--;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<vector<bool>>> vis(n, vector<vector<bool>>(m, vector<bool>(4, false)));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }
    int cur = d;
    int len = 1;
    while(1){
        if(vis[x][y][cur]){
            cout << "Forever!\n";
            return ;
        }
        vis[x][y][cur] = true;
        int nx = x + dx[cur];
        int ny = y + dy[cur];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m){
            cout << len << "\n";
            return ;
        }
        if(grid[nx][ny] == '/' || grid[nx][ny] == '\\'){
            if(grid[nx][ny] == '/'){
                cur = dir[cur];
            }else{
                cur = rdir[cur];
            }
        }
        x = nx;
        y = ny;
        len++;
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}