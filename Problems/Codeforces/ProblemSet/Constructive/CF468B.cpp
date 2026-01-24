#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

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


void solve() {  
    int n, a, b;
    cin >> n >> a >> b;
    map<int,int> mp;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
        mp[p[i]] = i;
    }
    SCC g(2 * n);
    for(int i = 1; i <= n; i++) {
        if(mp.contains(a - p[i])) {
            g.addEdge(i, mp[a - p[i]]);
            g.addEdge(n + mp[a - p[i]], n + i);
        } else {
            g.addEdge(i, n + i);
        }
        if(mp.contains(b - p[i])) {
            g.addEdge(n + i, n + mp[b - p[i]]);
            g.addEdge(mp[b - p[i]], i);
        } else {
            g.addEdge(n + i, i);
        }
    } 
    auto bel = g.work();
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        if(bel[i] == bel[n + i]) {
            cout << "NO\n";
            return;
        }
        if(bel[i] < bel[n + i]) {
            ans[i] = 0;
        } else {
            ans[i] = 1;
        }
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
