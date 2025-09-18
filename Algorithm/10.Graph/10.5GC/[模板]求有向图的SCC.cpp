#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct SCC {
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;
    SCC() {}
    SCC(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        adj.assign(n + 1, {});
        dfn.assign(n + 1, -1);
        low.resize(n + 1);
        bel.assign(n + 1, -1);
        stk.clear();
        cur = cnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    void dfs(int x) {
        dfn[x] = low[x] = ++cur;
        stk.push_back(x);
        for(auto y : adj[x]) {
            if(dfn[y] == -1) {
                dfs(y);
                low[x] = min(low[x], low[y]);
            } else if(bel[y] == -1) {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if(dfn[x] == low[x]) {
            ++cnt;
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while(y != x);
        }
    }
    vector<int> work() {
        for(int i = 1; i <= n; i++) {
            if(dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};

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
