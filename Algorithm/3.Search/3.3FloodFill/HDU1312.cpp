#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(int m, int n){ 
    vector<vector<char>> a(n + 1, vector<char>(m + 1));
    int x, y;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == '@') {
                x = i;
                y = j;
                a[i][j] = '.';
            }
        }
    }
    int dir[5] = {-1, 0, 1, 0, -1};
    int ans = 0;
    auto dfs = [&](auto &&dfs, int x, int y) -> void {
        if(x <= 0 || x > n || y <= 0 || y > m || a[x][y] != '.') {
            return ;
        }
        a[x][y] = '@';
        ans += 1;
        for(int i = 0; i < 4; i++) {
            dfs(dfs, x + dir[i], y + dir[i + 1]);
        }
    }; 
    dfs(dfs, x, y);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    while(cin >> n >> m && n) {
        solve(n, m);
    }
    return 0;
}   

