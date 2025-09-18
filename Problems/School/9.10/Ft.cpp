#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {-1, 0, 1, 0, -1};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }
    if(a[1][1] != 's') {
        cout << "No\n";
        return;
    }
    string s = "snuke";
    vector<vector<int>> vis(n + 1, vector<int>(m + 1));
    vector<vector<int>> memo(n + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int x, int y, int id) -> bool {
        if(x == n && y == m) {
            return true;
        }
        vis[x][y] = true;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i];
            int ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] != s[id] || vis[nx][ny] || memo[nx][ny]) {
                continue;
            }
            if(self(self, nx, ny, (id + 1) % 5)) {
                return true;
            } 
        }
        vis[x][y] = false;
        memo[x][y] = true;
        return false;
    };
    if(dfs(dfs, 1, 1, 1)) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
