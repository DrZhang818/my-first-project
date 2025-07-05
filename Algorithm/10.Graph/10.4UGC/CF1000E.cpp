#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    } 
    int tot = 0;   
    vector<int> dfn(n + 1), low(n + 1), id(n + 1);
    vector<vector<int>> edcc;
    stack<int> stk;
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        dfn[u] = low[u] = ++tot;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                self(v, u);
                low[u] = min(low[u], low[v]);
            } else if(v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            vector<int> cur;
            int t = edcc.size() + 1;
            while(1) {
                int v = stk.top();
                stk.pop();
                cur.push_back(v);
                id[v] = t;
                if(v == u) {
                    break;
                }
            }
            edcc.push_back(cur);
        }
    };
    dfs(1, 0);
    int cnt = edcc.size();
    vector<vector<int>> nadj(cnt + 1);
    for(int i = 1; i <= cnt; i++) {
        for(int u : edcc[i - 1]) {
            for(int v : adj[u]) {
                if(id[v] != i) {
                    nadj[i].push_back(id[v]);
                }
            }
        }
    }
    int len = 0, x = 0, y = 0;
    auto dfs2 = [&](this auto &&self, int u, int fa, int dep) -> void {
        if(dep > len) len = dep, x = u;
        for(int v : nadj[u]) if(v != fa) self(v, u, dep + 1);
    };
    dfs2(1, 0, 0);
    y = x, len = 0;
    dfs2(x, 0, 0);
    cout << len << "\n";
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
