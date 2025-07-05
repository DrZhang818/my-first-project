#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2515
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> c(n + 1), w(n + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= n; i++) cin >> c[i];
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i <= n; i++) {
        int j;
        cin >> j;
        if(j != 0) {
            adj[j].push_back(i);
        }
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
    vector<int> deg(cnt + 1), nc(cnt + 1), nw(cnt + 1);
    for(int u = 1; u <= n; u++) {
        nc[scc[u]] += c[u];
        nw[scc[u]] += w[u];
        for(int v : adj[u]) {
            if(scc[u] > scc[v]) {
                nadj[scc[u]].push_back(scc[v]);
                deg[scc[v]]++;
            }
        }
    }
    for(int i = 1; i <= cnt; i++) {
        sort(nadj[i].begin(), nadj[i].end());
        nadj[i].erase(unique(nadj[i].begin(), nadj[i].end()), nadj[i].end());
    }
    for(int i = 1; i <= cnt; i++) {
        if(!deg[i]) {
            nadj[0].push_back(i);
        }
    }
    
    vector<vector<int>> dp(cnt + 1, vector<int>(m + 1));
    auto dfs = [&](auto &&self, int u, int k) -> void {
        for(int v : nadj[u]) {
            for(int i = 0; i <= k - nc[v]; i++) {
                dp[v][i] = dp[u][i] + nw[v];
            }
            self(self, v, k - nc[v]);
            for(int i = nc[v]; i <= k; i++) {
                dp[u][i] = max(dp[u][i], dp[v][i - nc[v]]);
            }
        }   
    };
    dfs(dfs, 0, m);
    cout << dp[0][m] << "\n";
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
