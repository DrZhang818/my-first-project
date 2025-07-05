#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.lanqiao.cn/problems/89/learning/?page=1&first_category_id=1&second_category_id=3
void solve(){
    int n;
    cin >> n;
    vector<int> row(n), col(n);
    int dx[4]{1, 0, -1, 0};
    int dy[4]{0, 1, 0, -1};
    for(auto &c : col) cin >> c;
    for(auto &r : row) cin >> r;
    vector<vector<bool>> vis(n, vector<bool>(n, false));
    vector<int> path;
    function<bool(int,int)> dfs = [&](int x, int y) -> bool{
        if(x < 0 || x >= n || y < 0 || y >= n) return false;
        if(vis[x][y]) return false;
        if(row[x] == 0 || col[y] == 0) return false;
        if(row[x] == 1 && accumulate(row.begin(), row.begin() + x, 0) != 0) return false;
        if(col[y] == 1 && accumulate(col.begin(), col.begin() + y, 0) != 0) return false;        
        row[x]--;
        col[y]--;
        vis[x][y] = true;
        path.push_back(x * n + y);
        if(x == n - 1 && y == n - 1 &&
            accumulate(row.begin(), row.end(), 0) == 0 &&
            accumulate(col.begin(), col.end(), 0) == 0)  return true;
        for(int i = 0; i < 4; i++){
            if(dfs(x + dx[i], y + dy[i])) return true;
        }
        row[x]++;
        col[y]++;
        vis[x][y] = false;
        path.pop_back();
        return false;
    };
    dfs(0, 0);
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
