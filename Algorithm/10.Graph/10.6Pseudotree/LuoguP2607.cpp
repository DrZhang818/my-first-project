#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2607
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
        int v;
        cin >> v;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }
    vector<bool> vis(n + 1);
    int x = -1, y = -1;
    auto find = [&](auto &&find, int u, int fa) -> void {
        vis[u] = true;
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(!vis[v]) {
                find(find, v, u);
            } else {
                x = u, y = v;
            }
        }
    };
    vector<array<ll,2>> dp(n + 1);
    auto dfs = [&](auto &&dfs, int u, int fa) -> ll {
        dp[u][0] = 0, dp[u][1] = w[u];
        int cnt = 0;
        for(int v : adj[u]) {
            if(v == fa) continue;
            if(u == x && v == y || u == y && v == x) {
                if(cnt < 1) {
                    cnt++;
                    continue;
                }
            }
            dfs(dfs, v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
        return dp[u][0];
    };
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            find(find, i, 0);
            ll cur = max(dfs(dfs, x, 0), dfs(dfs, y, 0));
            ans += cur;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
