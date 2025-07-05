#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int MOD = 1e9 + 7;
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<vector<ll>> memo(n, vector<ll>(m, -1));
    auto dfs = [&](auto &&dfs, int x, int y) -> ll {
        if(x == n - 1 && y == m - 1) return 1;
        ll &res = memo[x][y];
        if(res != -1) return res;
        res = 0;
        if(x + 1 < n && a[x + 1][y] != '#') res = (res + dfs(dfs, x + 1, y)) % MOD;
        if(y + 1 < m && a[x][y + 1] != '#') res = (res + dfs(dfs, x, y + 1)) % MOD;
        return res;
    };
    ll ans = dfs(dfs, 0, 0);
    cout << ans % MOD << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
