#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//1-indexed
struct BlockCutTree {
    int n;
    vector<vector<int>> adj;
    vector<int> dfn, low, stk;
    int cnt, cur;
    vector<pair<int,int>> edges;
    BlockCutTree() {}
    BlockCutTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        stk.clear();
        cnt = cur = 0;
        edges.clear();
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x) {
        stk.push_back(x);
        dfn[x] = low[x] = cur++;
        for(auto y : adj[x]) {
            if(dfn[y] == -1) {
                dfs(y);
                low[x] = min(low[x], low[y]);
                if(low[y] == dfn[x]) {
                    int v;
                    do {
                        v = stk.back();
                        stk.pop_back();
                        edges.emplace_back(n + cnt, v);
                    } while (v != y);
                    edges.emplace_back(x, n + cnt);
                    cnt++;
                } 
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
    }
    pair<int,vector<pair<int,int>>> work() {
        for(int i = 1; i < n; i++) {
            if(dfn[i] == -1) {
                stk.clear();
                dfs(i);
            }
        }
        return {cnt, edges};
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    BlockCutTree t(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        t.addEdge(u, v);
    }
    auto [cnt, edges] = t.work();

    vector<vector<int>> tr(n + cnt + 1);
    for(auto [u, v] : edges) {
        tr[u].push_back(v);
    }

    vector<int> fa(n + cnt + 1);
    [&](this auto &&self, int x) -> void {
        for(auto y : tr[x]) {
            fa[y] = x;
            self(y);
        }
    }(1);

    int len = 0;
    vector<vector<array<int,2>>> e(cnt + 1);
    for(int x = 1; x <= n; x++) {
        for(int y : t.adj[x]) {
            if(x > y) {
                continue;
            }
            int z;
            if(fa[x] == fa[y] || (fa[x] != 0 && fa[fa[x]] == y)) {
                z = fa[x];
            } else {
                z = fa[y];
            }
            e[z - n].push_back({x, y});
        }
    }

    vector<int> vis(n + 1);
    vector<int> deg(n + 1);

    vector<vector<int>> adj(n + 1);
    for(int c = 1; c <= cnt; c++) {
        vector<int> point;
        for(auto [x, y] : e[c]) {
            if(vis[x] != c) {
                vis[x] = c;
                deg[x] = 0;
                point.push_back(x);
                adj[x].clear();
            }
            if(vis[y] != c) {
                vis[y] = c;
                deg[y] = 0;
                point.push_back(y);
                adj[y].clear();
            }
            deg[x]++;
            deg[y]++;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        vector<int> ends;
        for(auto x : point) {
            if(deg[x] > 2) {
                ends.push_back(x);
            }
        }
        if(ends.size() < 2) {
            assert(ends.size() == 0);
            if(e[c].size() > 1) {
                if(len && len != e[c].size()) {
                    cout << "No\n";
                    return;
                }
                len = e[c].size();
            }
            continue;
        }
        if(ends.size() > 2) {
            cout << "No\n";
            return;
        }
        int path = 0;
        int x = ends[0];
        int y = ends[1];
        for(auto u : adj[x]) {
            int res = 1;
            int v = x;
            while(u != y) {
                res++;
                v ^= adj[u][0] ^ adj[u][1];
                swap(u, v);
            }
            if(path && path != res) {
                cout << "No\n";
                return;
            }
            path = res;
        }
        if(len && len != 2 * path) {
            cout << "No\n";
            return;
        }
        len = 2 * path;
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
