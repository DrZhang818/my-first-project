#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    int x, y, w, s;
    friend bool operator<(const Info& a, const Info& b) {
        return a.w > b.w;
    }
};

void solve() {  
    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n + 1, vector<int>(m));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> b(n, vector<int>(m + 1));
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> b[i][j];
        }
    }
    
    priority_queue<Info> q;
    q.push({1, 1, 0, 0});

    vector<vector<array<int,2>>> dis(n + 1, vector<array<int,2>>(m + 1, {inf,inf}));
    dis[1][1][0] = 0;

    vector<vector<array<bool,2>>> vis(n + 1, vector<array<bool,2>>(m + 1, {false, false}));

    while(!q.empty()) {
        auto [x, y, w, s] = q.top(); q.pop();
        if(vis[x][y][s]) {
            continue;
        }
        vis[x][y][s] = true;
        if(x == n && y == m) {
            cout << w << "\n";
            return;
        }
        if(s == 0) {
            if(x + 1 <= n && w + b[x][y] < dis[x + 1][y][0]) {
                dis[x + 1][y][0] = w + b[x][y];
                q.push({x + 1, y, w + b[x][y], 0});
            }
            if(y + 1 <= m && w + a[x][y] < dis[x][y + 1][0]) {
                dis[x][y + 1][0] = w + a[x][y];
                q.push({x, y + 1, w + a[x][y], 0});
            }
            if(y - 1 >= 1 && w + a[x][y - 1] < dis[x][y - 1][0]) {
                dis[x][y - 1][0] = w + a[x][y - 1];
                q.push({x, y - 1, w + a[x][y - 1], 0});
            }
            if(w + 1 < dis[x][y][1]) {
                dis[x][y][1] = w + 1;
                q.push({x, y, w + 1, 1});
            }
        } else {
            if(x - 1 >= 1 && w + 1 < dis[x - 1][y][1]) {
                dis[x - 1][y][1] = w + 1;
                q.push({x - 1, y, w + 1, 1});
            }
            if(w < dis[x][y][0]) {
                dis[x][y][0] = w;
                q.push({x, y, w, 0});
            }
        }
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
