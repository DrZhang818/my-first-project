#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;


int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
char dir[] = {'U', 'D', 'L', 'R'};

void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<bool>> memo(n, vector<bool>(m, false));
    for(auto& r : grid){
        for(auto& c : r){
            cin >> c;
        }
    }
    auto dfs = [&](auto&& dfs, int x, int y) -> void{
        memo[x][y] = true;
        if(vis[x][y]) return;
        char c = grid[x][y];
        if(c != '?'){
            int i = 0;
            for(; i < 4; i++){
                if(dir[i] == c) break;
            }

            int nx = x + dx[i], ny = y + dy[i];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m){
                vis[x][y] = true;
            }
            else{
                if(memo[nx][ny]){
                    vis[x][y] = vis[nx][ny];
                    return;
                }
                dfs(dfs, nx, ny);
                if(vis[nx][ny]){
                    vis[x][y] = true;
                }
            }
        }
    };
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            dfs(dfs, i, j);
        }
    }  
    int ans = 0;
    for(int x = 0; x < n; x++){
        for(int y = 0; y < m; y++){
            char c = grid[x][y];
            if(c == '?'){
                bool ok = true;
                for(int k = 0; k < 4; k++){
                    int nx = x + dx[k], ny = y + dy[k];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if(!vis[nx][ny]) {
                        ok = false;
                        break;
                    }
                }
                if(ok){
                    vis[x][y] = true;
                }
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!vis[i][j]) ans++;
        }
    }
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
