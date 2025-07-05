#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


int n, m;
void solve() {
    vector<vector<int>> adj(2 * n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u++, v++;
        adj[u + x * n].push_back(v + !y * n);
        adj[v + y * n].push_back(u + !x * n);
    }
    vector<int> dfn(2 * n + 1), low(2 * n + 1), scc(2 * n + 1);
    int timer = 0, cnt = 0;
    stack<int> stk;
    auto dfs = [&](auto &&dfs, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                dfs(dfs, v);
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
    for(int i = 1; i <= 2 * n; i++) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(scc[i] == scc[i + n]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
