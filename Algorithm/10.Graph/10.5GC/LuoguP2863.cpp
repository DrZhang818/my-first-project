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
    }
    vector<int> dfn(n + 1), low(n + 1), scc(n + 1);
    int timer = 0, cnt = 0;
    stack<int> stk;
    int ans = 0;
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
            int c = 0;
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                c++;
                if(v == u) break;
            }
            if(c > 1) {
                ans++;
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            tarjan(tarjan, i);
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
