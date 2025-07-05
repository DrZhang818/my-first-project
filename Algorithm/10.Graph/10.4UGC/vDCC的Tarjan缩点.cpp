#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1), dcc(n + 1), nadj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if(u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    vector<int> dfn(n + 1), low(n + 1), cut(n + 1);
    int root, tot = 0, num = 0, cnt = 0;
    stack<int> stk;
    auto dfs = [&](auto &&dfs, int u) -> void {
        dfn[u] = low[u] = ++tot;
        stk.push(u);
        if(adj[u].empty()) {
            stk.pop();
            dcc[++cnt].push_back(u);
            return ;
        } 
        int child = 0;
        for(int v : adj[u]) {
            if(!dfn[v]) {
                dfs(dfs, v);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    child++;
                    if(u != root || child > 1) cut[u] = 1;
                    cnt++;
                    while(1) {
                        int x = stk.top();
                        stk.pop();
                        dcc[cnt].push_back(x);
                        if(x == v) break;
                    }
                    dcc[cnt].push_back(u);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    for(root = 1; root <= n; root++) {
        if(!dfn[root]) {
            dfs(dfs, root);
        }
    }
    num = cnt;
    for(int i = 1; i <= n; i++) {
        if(cut[i]) cut[i] = ++num;
    }
    for(int i = 1; i <= cnt; i++) {
        for(int x : dcc[i]) {
            if(cut[x]) {
                nadj[i].push_back(cut[x]);
                nadj[cut[x]].push_back(i);
            }
        }
    }
    cout << cnt << "\n";
    for(int i = 1; i <= cnt; i++) {
        int sz = dcc[i].size();
        cout << sz << " ";
        for(int j = 0; j < sz; j++) {
            cout << dcc[i][j] << " \n"[j == sz - 1];
        }
    } 
    auto pre_order = [&](this auto &&pre_order, int u, int fa) -> void {
        cout << u << " ";
        for(int v : nadj[u]) {
            if(v == fa) continue;
            pre_order(v, u);
        }
    };
    pre_order(1, 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
