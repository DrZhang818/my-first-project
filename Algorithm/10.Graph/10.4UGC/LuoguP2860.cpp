#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int u, idx;
};
int n, m, timer = 0;
vector<vector<info>> adj;
vector<vector<int>> dcc;
vector<int> dfn, low, id, deg;
stack<int> stk;
void init() {
    adj.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
    id.resize(n + 1);
}
void dfs(int u, int pre) {
    dfn[u] = low[u] = ++timer;
    stk.push(u);
    for(auto [v, idx] : adj[u]) {
        if(idx == (pre ^ 1)) continue;
        if(!dfn[v]) {
            dfs(v, idx);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        vector<int> vec;
        while(1) {
            int v = stk.top(); stk.pop();
            vec.push_back(v);
            id[v] = dcc.size();
            if(v == u) break;
        }
        dcc.push_back(vec);
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
    dfs(1, 0);
    int sz = dcc.size();
    deg.resize(sz);
    for(int u = 1; u <= n; u++) {
        for(auto [v, _] : adj[u]) {
            if(low[u] != low[v]) {
                deg[id[v]]++;
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < sz; i++) {
        cnt += deg[i] == 1;
    }
    cout << (cnt + 1) / 2 << "\n";
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
