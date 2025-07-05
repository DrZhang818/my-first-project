#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

struct DSU {
    vector<int> fa;
    DSU(int n) : fa(n + 1) { iota(fa.begin(), fa.end(), 0); }
    int find(int o) { return fa[o] == o ? o : fa[o] = find(fa[o]); }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if(u != v) fa[u] = v;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        e[c].push_back({u, v});
    }
    vector<vector<int>> comp(m + 1, vector<int>(n + 1, 0));
    for(int c = 1; c <= m; c++) {
        if(e[c].empty()) continue;
        DSU g(n);
        for(auto &[u, v] : e[c]) g.merge(u, v);
        for(int i = 1; i <= n; i++) comp[c][i] = g.find(i);
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        int ans = 0;
        for(int c = 1; c <= m; c++) {
            if(e[c].empty()) continue;
            ans += comp[c][u] == comp[c][v];
        }
        cout << ans << "\n";
    }
}




//Floyd求解传递闭包(非正解)
void solve1() { 
    int n, m;
    cin >> n >> m;
    vector adj(m + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, 0)));
    for(int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[c][u][v] = adj[c][v][u] = 1;
    }
    for(int c = 1; c <= m; c++) {
        for(int k = 1; k <= n; k++) {
            for(int i = 1; i <= n; i++) {
                if(adj[c][i][k] == 0) continue;
                for(int j = 1; j <= n; j++) {
                    if(adj[c][k][j] == 0) continue;
                    adj[c][i][j] = 1;
                }
            }
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int u, v;
        cin >> u >> v;
        int ans = 0;
        for(int c = 1; c <= m; c++) {
            if(adj[c][u][v]) {
                ans++;
            }
        }
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
