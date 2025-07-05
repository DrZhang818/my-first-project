#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int u, id;
};
int n, m, timer = 0;
vector<vector<info>> adj;
vector<int> dfn, low;
vector<vector<int>> dcc;
stack<int> stk;
void init() {
    adj.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
}
void dfs(int u, int pre) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    for(auto [v, id] : adj[u]) {
        if(id == (pre ^ 1)) continue;
        if(!dfn[v]) {
            dfs(v, id);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        vector<int> a;
        while(1) {
            int v = stk.top(); stk.pop();
            a.push_back(v);
            if(v == u) break;
        }
        dcc.push_back(a);
    }
}
void solve() {
    cin >> n >> m;
    init();
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({v, i << 1});
        adj[v].push_back({u, i << 1 | 1});
    }
    for(int i = 1; i <= n; i++) low[i] = i;
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            dfs(i, 0);
        }
    }
    int sz = dcc.size();
    cout << sz << "\n";
    for(int i = 0; i < sz; i++) {
        cout << dcc[i].size() << " ";
        for(int x : dcc[i]) {
            cout << x << " ";
        }
        cout << "\n";
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
