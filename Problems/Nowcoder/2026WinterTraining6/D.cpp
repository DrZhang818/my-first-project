#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct Info {
    int x, y, t;
    friend bool operator<(const Info& a, const Info& b) {
        return a.t > b.t;
    }
};

int dir[] = {-1, 0, 1, 0, -1};

void solve() {  
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    vector<Info> a(p + 1), b(q + 1);

    vector<vector<int>> tag(n + 1, vector<int>(m + 1));

    for(int i = 1; i <= p; i++) {
        cin >> a[i].x >> a[i].y;
    }
    for(int i = 1; i <= q; i++) {
        int x, y, t;
        cin >> x >> y >> t;
        tag[x][y] = t;
    }

    vector<vector<int>> dis(n + 1, vector<int>(m + 1, -1));
    priority_queue<Info> pq;
    for(int i = 1; i <= p; i++) {
        pq.push({a[i].x, a[i].y, 0});
        dis[a[i].x][a[i].y] = 0;
    }

    while(!pq.empty()) {
        auto [x, y, t] = pq.top(); pq.pop();
        for(int i = 0; i < 4; i++) {
            int nx = x + dir[i], ny = y + dir[i + 1];
            if(nx < 1 || nx > n || ny < 1 || ny > m || dis[nx][ny] != -1) continue;
            if(t + 1 >= tag[nx][ny]) {
                dis[nx][ny] = t + 1;
                pq.push({nx, ny, t + 1});
            } else {
                dis[nx][ny] = tag[nx][ny];
                pq.push({nx, ny, tag[nx][ny]});
            }
        }
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            ans = max(ans, dis[i][j]);
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
