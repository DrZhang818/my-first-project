#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2746
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int u = 1; u <= n; u++) {
        int v;
        while(cin >> v) {
            if(v == 0) break;
            adj[u].push_back(v);
        }
    }
    vector<int> dfn(n + 1), low(n + 1), scc(n + 1);
    int timer = 0, cnt = 0;
    stack<int> stk;
    auto dfs = [&](auto &&self, int u) -> void {
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
            while(1) {
                int v = stk.top(); stk.pop();
                scc[v] = cnt;
                if(v == u) break;
            }
        }
    };
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    } 
    vector<int> indeg(cnt + 1), outdeg(cnt + 1);
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            if(scc[u] > scc[v]) {
                outdeg[scc[u]]++;
                indeg[scc[v]]++;
            }
        }
    }
    int a1 = 0, a2 = 0;
    for(int i = 1; i <= cnt; i++) {
        if(indeg[i] == 0) a1++;
        if(outdeg[i] == 0) a2++;
    }
    cout << a1 << "\n";
    if(cnt == 1) {
        cout << 0 << "\n";
    } else {
        cout << max(a1, a2) << "\n";
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