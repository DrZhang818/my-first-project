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