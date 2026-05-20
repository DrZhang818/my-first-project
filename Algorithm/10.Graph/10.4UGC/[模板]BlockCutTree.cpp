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