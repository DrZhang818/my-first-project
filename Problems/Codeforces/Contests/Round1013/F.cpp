#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
constexpr int MOD = 998244353;
void solve() { 
    int n, m, d;
    cin >> n >> m >> d;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = "$" + a[i];
    }
    vector<vector<int>> pre(n + 1);
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        bool ok2 = false;
        for(int j = 1; j <= m; j++) {
            if(a[i][j] == 'X') {
                ok2 = true;
                pre[i].push_back(j);
            }
        }
        if(!ok2) {
            ok = false;
            break;
        }
    }
    if(!ok) {
        cout << 0 << "\n";
        return;
    }
    vector memo(n + 1, vector<vector<ll>>(m + 1, vector<ll>(2, -1)));
    auto dfs = [&](this auto &&dfs, int x, int y, int cnt) -> ll {
        ll &res = memo[x][y][cnt];
        if(res != -1) return res;
        res = 0;
        if(cnt == 0) {
            int l = lower_bound(pre[x].begin(), pre[x].end(), max(0, y - d)) - pre[x].begin();
            int r = upper_bound(pre[x].begin(), pre[x].end(), min(m, y + d)) - pre[x].begin() - 1;
            for(int j = l; j <= r; j++) {
                if(pre[x][j] == y) continue;
                res = (res + dfs(x, pre[x][j], 1)) % MOD;
            }
        }
        if(x == 1) {
            res = (res + 1) % MOD;
        }
        else {
            int delta = sqrt(d * d - 1);
            int l = lower_bound(pre[x - 1].begin(), pre[x - 1].end(), max(0, y - delta)) - pre[x - 1].begin();
            int r = upper_bound(pre[x - 1].begin(), pre[x - 1].end(), min(m, y + delta)) - pre[x - 1].begin() - 1;
            for(int j = l; j <= r; j++) {
                res = (res + dfs(x - 1, pre[x - 1][j], 0)) % MOD;
            }
        }
        res %= MOD;
        return res;
    };

    ll ans = 0;
    for(int j = 0; j < pre[n].size(); j++) {
        ans = (ans + dfs(n, pre[n][j], 0)) % MOD;
    }
    cout << ans % MOD << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
