#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n, m, timer = 0, cnt = 0, ans = 0;
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
    stk.push(u);
    instk[u] = true;
    for(int v : adj[u]) {
        if(!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else if(instk[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        cnt++;
        int sz = 0;
        while(1) {
            int v = stk.top(); stk.pop();
            sz++;
            instk[v] = false;
            scc[v] = cnt;
            if(v == u) break;
        }
        if(sz > 1) ans++;
    }
}
void solve() {
    cin >> n >> m;
    init();
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            dfs(i, 0);
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
