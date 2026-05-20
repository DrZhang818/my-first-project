#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

pair<int,int> dir[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

struct Info {
    int x, y, s;
};

void solve() {
    int n, m, l, r;
    cin >> n >> m >> l >> r;

    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = "#" + a[i];
    }

    vector<vector<array<int, 2>>> dis(n + 1, vector<array<int, 2>>(m + 1, {inf, inf}));
    dis[1][1][0] = 0;

    queue<Info> q;
    q.emplace(1, 1, 0);
    while(!q.empty()) {
        auto [x, y, s] = q.front(); q.pop();
        for(int i = 0; i < 8; i++) {
            int nx = x + dir[i].first;
            int ny = y + dir[i].second;
            int ns = s ^ 1;
            if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '0' || dis[nx][ny][ns] <= dis[x][y][s] + 1) continue;
            dis[nx][ny][ns] = dis[x][y][s] + 1;
            q.emplace(nx, ny, ns);
        }
    }

    if(dis[n][m][0] == inf && dis[n][m][1] == inf) {
        cout << -1 << "\n";
        return; 
    }

    if(l != r) {
        int D = min(dis[n][m][0], dis[n][m][1]);
        cout << (D + r - 1) / r << "\n";
        return;
    }

    int ans = inf;

    if(dis[n][m][0] != inf) {
        int t = (dis[n][m][0] + r - 1) / r;
        if(r % 2 == 0) {
            ans = min(ans, t);
        } else {
            ans = min(ans, t + (t & 1));
        }
    }

    if(dis[n][m][1] != inf && r % 2 == 1) {
        int t = (dis[n][m][1] + r - 1) / r;
        ans = min(ans, t | 1);
    }

    if(ans == inf) {
        ans = -1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}