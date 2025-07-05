#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P5058
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1), dcc(n + 1);
    int x, y;
    while(cin >> x >> y) {
        if(x == 0 && y == 0) break;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    cin >> x >> y;

    vector<int> dfn(n + 1), low(n + 1), id(n + 1);
    vector<bool> cut(n + 1);
    int timer = 0, cnt = 0, rt = x;
    stack<int> stk;
    auto tarjan = [&](auto &&self, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        if(!adj[u].size()) {
            dcc[++cnt].push_back(u);
            stk.pop();
            return ; 
        }
        int son = 0;
        for(int v : adj[u]) {
            if(!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    son++;
                    if(u != rt || son > 1) {
                        cut[u] = true;
                    }
                    cnt++;
                    while(1) {
                        int w = stk.top(); stk.pop();
                        dcc[cnt].push_back(w);
                        id[w] = cnt;
                        if(w == v) break;
                    }
                    dcc[cnt].push_back(u);
                    id[u] = cnt;
                } 
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    tarjan(tarjan, x);
    int sz = cnt;
    for(int i = 1; i <= n; i++) {
        if(cut[i]) {
            id[i] = i + n;
            sz = i + n;
        }
    }
    vector<vector<int>> nadj(sz + 1);
    for(int i = 1; i <= cnt; i++) {
        for(int j : dcc[i]) {
            if(cut[j]) {
                nadj[id[j]].push_back(i);
                nadj[i].push_back(id[j]);
            }
        }
    }
    vector<int> fa(sz + 1);
    x = id[x], y = id[y];
    auto dfs = [&](auto &&self, int u, int f) -> void {
        fa[u] = f;
        for(int v : nadj[u]) {
            if(v != f) {
                self(self, v, u);
            }
        }
    };
    dfs(dfs, x, 0);
    int ans = inf;
    while(y != x) {
        y = fa[y];
        if(x != y && y > n) {
            ans = min(ans, y - n);
        }
    }
    if(ans == inf) {
        cout << "No solution\n";
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
