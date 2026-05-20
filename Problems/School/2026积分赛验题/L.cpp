#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int dir[] = {-1, 0, 1, 0, -1};

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<bool>> vis(n, vector<bool>(m));

    auto dfs = [&](this auto&& self, int x, int y) -> void {
        vis[x][y] = true;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i];
            int ny = y + dir[i + 1];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] != a[x][y]) {
                continue;
            }
            if(!vis[nx][ny]) {
                self(nx, ny);
            }
        }
    };

    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '1' && !vis[i][j]) {
                ans++;
                dfs(i, j);
            }
        }
    }

    cout << ans << "\n";
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
