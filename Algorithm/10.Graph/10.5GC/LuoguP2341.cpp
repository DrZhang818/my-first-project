#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2341
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
    auto tarjan = [&](auto &&tarjan, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        for(int v : adj[u]) {
            if(!dfn[v]) {
                tarjan(tarjan, v);
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
    vector<int> outdeg(cnt + 1);
    int ans = 0;
    for(int u = 1; u <= n; u++) {
        if(scc[u] == 1) ans++;
        for(int v : adj[u]) {
            if(scc[u] > scc[v]) {
                outdeg[scc[u]]++;
            }
        }
    }
    int c = 0;
    for(int i = 1; i <= cnt; i++) {
        if(!outdeg[i]) {
            c++;
        }
    }
    if(c > 1) {
        cout << 0 << "\n";
    } else {
        cout << ans << "\n";
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
