#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


// void solve(){
//     int n, m, k;
//     cin >> n >> m >> k;
//     int dx[4] = {-1, 0, 1, 0};
//     int dy[4] = {0, 1, 0, -1};
//     vector<string> grid(n);
//     for(int i = 0; i < n; i++){
//         cin >> grid[i];
//     }
//     int sx, sy, ex, ey;
//     cin >> sx >> sy >> ex >> ey;
//     sx -= 1;
//     sy -= 1;
//     ex -= 1;
//     ey -= 1;
//     vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
//     auto dfs = [&](auto&& dfs, int x, int y) -> int{
//         if(x < 0 || x >= n || y < 0 || y >= m){
//             return INT_MAX / 2;
//         }
//         if(grid[x][y] == '#') return INT_MAX / 2;
//         if(x == sx && y == sy) return 0;
//         int &res = memo[x][y];
//         if(res != -1) return res;
//         res = INT_MAX / 2;
//         for(int i = 0; i < 4; i++){
//             int nx = x, ny = y;
//             int st = 0;
//             while(grid[nx][ny] != '#' && st < k){
//                 nx += dx[i];
//                 ny += dy[i];
//                 if(nx < 0 || nx >= n || ny < 0 || ny >= m){
//                     nx -= dx[i];
//                     ny -= dy[i];
//                     break;
//                 }
//                 st++;
//             }
//             if(grid[nx][ny] == '#') st--;
//             for(int j = 1; j <= st; j++){
//                 res = min(res, 1 + dfs(dfs, x + j * dx[i], y + j * dy[i]));
//             }
//         }
//         return res;
//     };
//     int ans = dfs(dfs, ex, ey);
//     if(ans >= INT_MAX / 2){
//         cout << -1 << "\n";
//     }else{
//         cout << ans << "\n";
//     }
// }
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    vector<string> grid(n);
    for(int i = 0; i < n; i++){
        cin >> grid[i];
    }
    int sx, sy, ex, ey;
    cin >> sx >> sy >> ex >> ey;
    sx -= 1;
    sy -= 1;
    ex -= 1;
    ey -= 1;
    
    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(m, INF));
    dist[ex][ey] = 0;
    
    queue<pair<int, int>> q;
    q.push({ex, ey});
    
    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        for(int i = 0; i < 4; i++){
            for(int step = 1; step <= k; step++){
                int nx = x + dx[i] * step;
                int ny = y + dy[i] * step;
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#') break;
                if(dist[nx][ny] > dist[x][y] + 1){
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
                else if(dist[nx][ny] < dist[x][y] + 1){
                    break;
                }
            }
        }
    }
    if(dist[sx][sy] == INF){
        cout << -1 << "\n";
    }
    else{
        cout << dist[sx][sy] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}