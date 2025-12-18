#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int dir[] = {-1, 0, 1, 0, -1};

struct Info {
    int x, y, w;
    friend bool operator<(const Info& a, const Info& b) {
        return a.w > b.w;
    }
};

void solve() {  
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<char>(m + 1));
    array<vector<PII>, 26> adj;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(isalpha(a[i][j])) {
                adj[a[i][j] - 'a'].push_back({i, j});
            }
        }
    }
    vector dis(n + 1, vector<int>(m + 1, inf));
    dis[1][1] = 0;
    vector vis(n + 1, vector<bool>(m + 1));
    vector<bool> vis2(26);
    priority_queue<Info> q;
    q.push({1, 1, 0});
    while(!q.empty()) {
        auto [x, y, w] = q.top(); q.pop();
        if(vis[x][y]) continue;
        vis[x][y] = true;
        if(x == n && y == m) break;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || vis[nx][ny] || a[nx][ny] == '#') continue;
            if(w + 1 < dis[nx][ny]) {
                dis[nx][ny] = w + 1;
                q.push({nx, ny, w + 1});
            }
        }
        if(isalpha(a[x][y])) {
            if(!vis2[a[x][y] - 'a']) {
                vis2[a[x][y] - 'a'] = true;
                for(auto [nx, ny] : adj[a[x][y] - 'a']) {
                    if(w + 1 < dis[nx][ny]) {
                        dis[nx][ny] = w + 1;
                        q.push({nx, ny, w + 1});
                    }
                }
            }
        }
    }
    if(dis[n][m] == inf) {
        cout << -1 << "\n";
        return;
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
