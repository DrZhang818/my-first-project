#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> dfn(n + 1), low(n + 1), scc(n + 1);
    int timer = 0, cnt = 0;
    stack<int> stk;
    auto tarjan = [&](auto &&self, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else if(!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            ++cnt;
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                if(v == u) break;
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(tarjan, i);
        }
    }
    vector<vector<int>> nadj(cnt + 1);
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            if(scc[u] > scc[v]) {
                nadj[scc[u]].push_back(scc[v]);
            }
        }
    }
    for(int i = 1; i <= cnt; i++) {
        sort(nadj[i].begin(), nadj[i].end());
        nadj[i].erase(unique(nadj[i].begin(), nadj[i].end()), nadj[i].end());
    }
    vector<bool> vis(cnt + 1);
    vector<int> sz(cnt + 1);
    vector<PII> dp(cnt + 1);  
    for(int i = 1; i <= n; i++) {
        sz[scc[i]]++;
    }
    auto dfs = [&](auto &&self, int u) -> PII {
        if(vis[u]) return dp[u];
        vis[u] = true;
        int mx = 0, cnt = 1;
        for(int v : nadj[u]) {
            self(self, v);
            if(dp[v].first > mx) {
                mx = dp[v].first;
                cnt = dp[v].second % x;
            } else if(dp[v].first == mx) {
                cnt = (cnt + dp[v].second) % x;
            }
        }
        return dp[u] = {mx + sz[u], cnt};
    };
    for(int i = 1; i <= cnt; i++) {
        nadj[0].push_back(i);
    }
    dfs(dfs, 0);
    cout << dp[0].first << "\n" << dp[0].second << "\n";
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
