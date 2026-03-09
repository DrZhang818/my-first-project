#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct Info {
    int x, t;
};

int dis[1005][2520];
int cost[1005][2520];
vector<Info> q[105];

void solve() {
    int n;
    cin >> n;
    vector<int> c(n + 1);
    vector<vector<int>> h(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
        h[i].resize(c[i]);
        for(int j = 0; j < c[i]; j++) {
            cin >> h[i][j];
        }
    }    

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 2520; j++) {
            cost[i][j] = h[i][j % c[i]];
        }
    }

    memset(dis, 0x3f, sizeof(dis));

    dis[0][0] = 0;
    q[0].emplace_back(0, 0);

    int cnt = 1;
    int cur_d = 0;

    while(cnt > 0) {
        if(q[cur_d % 105].empty()) {
            cur_d++;
            continue;
        }

        auto [x, t] = q[cur_d % 105].back();
        q[cur_d % 105].pop_back();
        cnt--;

        if(dis[x][t] < cur_d) {
            continue;
        }

        if(x == n + 1) {
            cout << cur_d << "\n";
            return;
        }

        int nt = t + 1;
        if(nt == 2520) nt = 0;

        for(int nx : {x - 1, x, x + 1}) {
            if(nx < 0 || nx > n + 1) continue;
            int w = cost[nx][nt];
            if(dis[nx][nt] > cur_d + w) {
                dis[nx][nt] = cur_d + w;
                q[dis[nx][nt] % 105].emplace_back(nx, nt);
                cnt++;
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
