#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y;
};

int dir[5] = {-1, 0, 1, 0, -1};

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<char>(m + 1));
    int ans = 0;
    vector<info> q;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == '#') {
                q.emplace_back(i, j);
                ans += 1;
            }
        }
    }
    while(!q.empty()) {
        vector<info> nq;
        for(auto [x, y] : q) {
            for(int i = 0; i < 4; i++) {
                int nx = x + dir[i], ny = y + dir[i + 1];
                if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#') {
                    continue;
                }
                int cnt = 0;
                for(int j = 0; j < 4; j++) {
                    int nnx = nx + dir[j], nny = ny + dir[j + 1];
                    if(nnx < 1 || nnx > n || nny < 1 || nny > m || a[nnx][nny] == '.') {
                        continue;
                    }
                    cnt++;
                }
                if(cnt == 1) {
                    ans += 1;
                    nq.emplace_back(nx, ny);
                }
            }
        }
        for(auto [x, y] : nq) {
            a[x][y] = '#';
        }
        swap(q, nq);
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
