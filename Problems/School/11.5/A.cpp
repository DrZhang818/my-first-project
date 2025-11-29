#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y, c;
    friend bool operator < (const info &a, const info &b) {
        return a.c > b.c;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> A(n + 1, vector<int>(m));
    vector<vector<int>> B(n, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < m; j++) {
            cin >> A[i][j];
        }
    }
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> B[i][j];
        }
    }

    vector<vector<int>> dis(n + 1, vector<int>(m + 1, inf));
    dis[1][1] = 0;
    vector<vector<bool>> vis(n + 1, vector<bool>(m + 1));
    priority_queue<info> q;
    q.push({1, 1, 0});
    auto update = [&](int x, int y, int nx, int ny, ll cost) -> void {
        if(dis[nx][ny] <= cost) {
            return;
        }
        dis[nx][ny] = cost;
        q.push({nx, ny, (int)cost});
    };
    while(!q.empty()) {
        auto [x, y, c] = q.top(); q.pop();
        if(x == n && y == m) break;
        if(vis[x][y]) continue;
        vis[x][y] = true;
        if(y < m) update(x, y, x, y + 1, dis[x][y] + A[x][y]);
        if(y > 1) update(x, y, x, y - 1, dis[x][y] + A[x][y - 1]);
        if(x < n) update(x, y, x + 1, y, dis[x][y] + B[x][y]);
        for(int i = 1; i < x; i++) {
            if(dis[x - i][y] >= dis[x][y] + 1 + i) {
                update(x, y, x - i, y, dis[x][y] + 1 + i);
            } else {
                break;
            }
        }
    }
    cout << dis[n][m] << "\n";
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
