#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://loj.ac/p/2632
//https://www.luogu.com.cn/problem/P4667
struct info {
    int x, y, s, cost;
};
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = c == '/' ? 1 : 0;
        }
    }
    vector<tuple<int,int,int>> moves[2];
    moves[0] = {
        {+1, 0, 1},
        {0, +1, 1},
        {+1, +1, 0},
        {-1, 0, 1},
        {0, -1, 1},
        {-1, -1, 0}
    };
    moves[1] = {
        {+1, 0, 0},
        {0, -1, 0}, 
        {+1, -1, 1},
        {-1, 0, 0},
        {0, +1, 0}, 
        {-1, +1, 1}
    };
    const int inf = 1000000000;
    vector dist(n + 1, vector<vector<int>>(m + 1, vector<int>(2, inf)));
    deque<info> q;
    dist[1][1][0] = a[1][1] == 1;
    q.push_back({1, 1, 0, dist[1][1][0]});
    while(!q.empty()) {
        auto [x, y, s, cost] = q.front(); q.pop_front();
        if(cost != dist[x][y][s]) continue;
        if(x == n && y == m && s == 0) { cout << cost << "\n"; return; }
        for(auto [dx, dy, ns] : moves[s]) {
            int nx = x + dx, ny = y + dy;
            if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
            int flag = a[nx][ny] != ns;
            int ncost = cost + flag;
            if(ncost < dist[nx][ny][ns]) {
                dist[nx][ny][ns] = ncost;
                if(flag) q.push_back({nx, ny, ns, ncost});
                else q.push_front({nx, ny, ns, ncost});
            }
        }
    }
    cout << "NO SOLUTION\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
