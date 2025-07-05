#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    vector<vector<int>> memo(n, vector<int>(n, -1));
    vector<int> size;
    int id = 0;
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    auto dfs = [&](auto&& dfs, int x, int y)->void{
        memo[x][y] = id;
        size[id]++;
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= n){
                continue;
            }
            if(grid[nx][ny] != grid[x][y] && memo[nx][ny] == -1){
                dfs(dfs, nx, ny);
            }
        }
    };
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(memo[i][j] == -1){
                size.push_back(0);
                dfs(dfs, i, j);
                id++;
            }
        }
    }
    while(m--){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        int id = memo[x][y];
        cout << size[id] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}