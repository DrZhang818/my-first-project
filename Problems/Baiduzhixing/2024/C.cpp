#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1001;

int dir[] = {-1, 0, 1, 0, -1};

void solve() {  
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;
    vector<vector<int>> a(N + 1, vector<int>(N + 1));
    vector<vector<int>> dis(N + 1, vector<int>(N + 1, inf));
    vector<vector<int>> vis(N + 1, vector<int>(N + 1));
    dis[x1][y1] = 0;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        a[x][y] = 1;
    }
    deque<PII> q;
    q.push_back({x1, y1});
    while(!q.empty()) {
        auto [x, y] = q.front(); q.pop_front();
        if(vis[x][y]) continue;
        vis[x][y] = true;
        if(x == x2 && y == y2) break;
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 0 || nx > N || ny < 0 || ny > N || vis[nx][ny]) {
                continue;
            }
            int w = dis[x][y], nw = a[nx][ny];
            if(w + nw < dis[nx][ny]) {
                dis[nx][ny] = w + nw;
                if(nw == 0) {
                    q.push_front({nx, ny});
                } else {
                    q.push_back({nx, ny});
                }
            }
        }
    }
    cout << dis[x2][y2] << "\n";
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
