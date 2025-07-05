#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P1656
struct info {
    int u, v;
    friend bool operator < (const info &a, const info &b) {
        if(a.u != b.u) return a.u < b.u;
        return a.v < b.v;
    }
};
int n, m, timer = 0;
vector<vector<int>> adj;
vector<info> ans;
vector<int> dfn, low;
void init() {
    adj.resize(n + 1);
    dfn.resize(n + 1);
    low.resize(n + 1);
}
void dfs(int u, int fa) {
    dfn[u] = low[u] = timer++;
    for(int v : adj[u]) {
        if(!dfn[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) {
                if(u > v) ans.push_back({v, u});
                else ans.push_back({u, v});
            }
        } else if(v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
void solve() {
    cin >> n >> m;
    init();
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    sort(ans.begin(), ans.end());
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
