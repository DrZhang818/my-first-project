#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int n, m;
vector<vector<int>> adj;
vector<int> dfn, low, scc;
int timer = 0, cnt = 0;
stack<int> stk;
void init() {
    adj.assign(2 * n + 1, vector<int>());
    dfn.assign(2 * n + 1, 0);
    low.assign(2 * n + 1, 0);
    scc.assign(2 * n + 1, 0);
    timer = cnt = 0;
    while(!stk.empty()) stk.pop();
}
void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    for(int v : adj[u]) {
        if(!dfn[v]) {
            tarjan(v);
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
}
void solve() {
    n *= 3;
    init();
    for(int i = 1; i <= n / 3; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v + n);
        adj[u].push_back(w + n);
        adj[v].push_back(u + n);
        adj[w].push_back(u + n);
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u + n].push_back(v);
        adj[v + n].push_back(u);
    }
    for(int i = 1; i <= 2 * n; i++) {
        if(!dfn[i]) {
            tarjan(i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(scc[i] == scc[i + n]) {
            cout << "no\n";
            return;
        }
    }
    cout << "yes\n";
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n >> m) {
        solve();
    }
    return 0;
}
