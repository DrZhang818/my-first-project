#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using db = double;
using u64 = unsigned long long;

//1-indexed
struct BlockCutTree {
    int n, cnt;
    vector<vector<int>> adj, bct;
    vector<int> dfn, low, stk;

    BlockCutTree(int n) : n(n), cnt(n), adj(n), bct(n << 1), dfn(n, 0), low(n, 0) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build() {
        int timer = 0;
        auto dfs = [&](auto&& self, int u) -> void {
            dfn[u] = low[u] = ++timer;
            stk.push_back(u);

            for(int v : adj[u]) {
                if(!dfn[v]) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);

                    if(low[v] == dfn[u]) {
                        int sq = cnt++;
                        int x;
                        do {
                            x = stk.back();
                            stk.pop_back();
                            bct[sq].push_back(x);
                            bct[x].push_back(sq);
                        } while(x != v);
                        bct[sq].push_back(u);
                        bct[u].push_back(sq);
                    }
                } else {
                    low[u] = min(low[u], dfn[v]);
                }
            }
        };

        for(int i = 1; i < n; i++) {
            if(!dfn[i]) {
                stk.clear();
                dfs(dfs, i);
            }
        }
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    int A, B, C;
    cin >> A >> B >> C;
    BlockCutTree tr(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        tr.addEdge(u, v);
    }

    tr.build();

    auto& bct = tr.bct;

    vector<int> p(n * 2 + 1);
    auto dfs = [&](auto&& self, int u, int fa) -> void {
        p[u] = fa;
        for(int v : bct[u]) {
            if(v == fa) continue;
            self(self, v, u);
        }
    };  
    dfs(dfs, A, 0);

    int tar = p[B];
    int x = C;
    while(x) {
        x = p[x];
        if(x == tar) {
            cout << "Yes\n";
            return;
        }
    }

    cout << "No\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}