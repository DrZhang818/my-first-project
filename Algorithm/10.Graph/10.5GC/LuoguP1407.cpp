#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P1407
void solve() {
    int n, m, id = 0;
    cin >> n;
    unordered_map<string,int> mp;
    vector<vector<int>> adj(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        string s, t;
        cin >> s >> t;
        mp[s] = ++id;
        mp[t] = id + n;
        adj[mp[s]].push_back(mp[t]);
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        string s, t;
        cin >> s >> t;
        adj[mp[t]].push_back(mp[s]);
    }
    vector<int> dfn(2 * n + 1), low(2 * n + 1), scc(2 * n + 1);
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
    for(int i = 1; i <= 2 * n; i++) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(scc[i] == scc[i + n]) {
            cout << "Unsafe\n"; 
        } else {
            cout << "Safe\n";
        }
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
