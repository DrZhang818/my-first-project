#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n, m, timer = 0, cnt = 0;
vector<vector<int>> adj;
vector<int> dfn, low, scc;
vector<bool> instk;
stack<int> stk;
void init() {
    adj.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
    scc.resize(n + 1);
    instk.resize(n + 1);
}
void dfs(int u, int fa) {
    dfn[u] = low[u] = ++timer;
    instk[u] = true;
    stk.push(u);
    for(int v : adj[u]) {
        if(!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        ++cnt;
        while(1) {
            int v = stk.top(); stk.pop();
            scc[v] = cnt;
            instk[v] = false;
            if(v == u) break;
        }
    }
}
void solve() {
    cin >> n >> m;
    init();
    vector<int> w(n + 1);
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); 
    }
    for(int u = 1; u <= n; u++) if(!dfn[u]) dfs(u, 0);
    vector<vector<int>> nadj(cnt + 1);
    vector<ll> nw(cnt + 1);
    for(int i = 1; i <= n; i++) {
        nw[scc[i]] += w[i];
    }
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            int x = scc[u], y = scc[v];
            if(x != y) {
                nadj[x].push_back(y);
            }
        }
    }
    ll ans = 0;
    vector<ll> dp(cnt + 1);
    for(int i = 1; i <= cnt; i++) {
        dp[i] = nw[i];
        for(int j : nadj[i]) {
            dp[i] = max(dp[i], dp[j] + nw[i]);
        }
        ans = max(ans, dp[i]);
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
