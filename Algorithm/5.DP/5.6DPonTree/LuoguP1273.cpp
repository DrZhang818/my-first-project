#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P1273
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> c(n + 1), w(n + 1);
    for(int i = 1; i <= n - m; i++) {
        int k;
        cin >> k;
        while(k--) {
            int v, x;
            cin >> v >> x;
            w[v] = -x;
            adj[i].push_back(v);
        }
    }
    for(int i = n - m + 1; i <= n; i++) {
        int x;
        cin >> x;
        w[i] += x;
        c[i] = 1;
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -inf));
    for(int i = 1; i <= n; i++) dp[i][0] = 0;
    auto dfs = [&](auto &&self, int u, int k) -> void {
        for(int v : adj[u]) {
            for(int i = 0; i <= k - c[v]; i++) {
                dp[v][i] = dp[u][i] + w[v];
            }
            self(self, v, k - c[v]);
            for(int i = c[v]; i <= k; i++) {
                dp[u][i] = max(dp[u][i], dp[v][i - c[v]]);
            }
        }
    };
    dfs(dfs, 1, m);
    for(int i = m; i >= 0; i--) {
        if(dp[1][i] >= 0) {
            cout << i << "\n";
            return;
        }
    }
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
