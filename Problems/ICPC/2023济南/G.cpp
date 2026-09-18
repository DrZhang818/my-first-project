#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;
constexpr int MOD = 1E9 + 7;

struct DSU {
    vector<int> fa;
    int sz;
    DSU(int n) : sz(n), fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return;
        fa[v] = u;
        sz--;
    }
    int query() {
        return sz;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> s(2 * n);
    int tot = 0;
    for(int i = 0; i < n; i++) {
        cin >> s[2 * i];
        tot += count(s[2 * i].begin(), s[2 * i].end(), '1');
        s[2 * i + 1] = s[2 * i];
        reverse(s[2 * i + 1].begin(), s[2 * i + 1].end());
    }
    if(tot > m) {
        cout << 0 << "\n";
        return;
    }

    vector<vector<int>> adj(2 * n);

    auto addEdge = [&](int x, int y) {
        adj[x].push_back(y);
        adj[y ^ 1].push_back(x ^ 1);
    };

    for(int j = 0; j < m; j++) {
        int pre = -1;
        for(int i = 0; i < 2 * n; i++) {
            if(s[i][j] == '0') continue;
            int npre = i;
            if(pre != -1) {
                int idx = adj.size();
                npre = idx;
                adj.emplace_back();
                adj.emplace_back();
                addEdge(pre, npre);
                addEdge(i, npre);
                addEdge(i, pre ^ 1);
            } 
            pre = npre;
        }
    }

    int sz = adj.size();
    vector<int> dfn(sz), low(sz), id(sz);
    vector<bool> instk(sz);
    stack<int> stk;
    int timer = 0, cnt = 0;

    auto dfs = [&](auto&& self, int u) -> void {
        dfn[u] = low[u] = ++timer;
        stk.push(u);
        instk[u] = true;
        for(int v : adj[u]) {
            if(!dfn[v]) {
                self(self, v);
                low[u] = min(low[u], low[v]);
            } else if(instk[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(low[u] == dfn[u]) {
            cnt++;
            while(1) {
                int v = stk.top();
                stk.pop();
                instk[v] = false;
                id[v] = cnt;
                if(v == u) break;
            }
        }
    };
    for(int i = 0; i < sz; i++) {
        if(!dfn[i]) {
            dfs(dfs, i);
        }
    }

    for(int i = 0; i < n; i++) {
        if(id[2 * i] == id[2 * i + 1]) {
            cout << 0 << "\n";
            return;
        }
    }

    DSU dsu(n);
    for(int j = 0; j < m; j++) {
        int las = -1;
        for(int i = 0; i < 2 * n; i++) {
            if(s[i][j] == '0') continue;
            if(las != -1) {
                dsu.merge(las, i / 2);
            }
            las = i / 2;
        }
    }

    int ans = 1, res = dsu.query();

    for(int i = 0; i < res; i++) {
        ans = 2LL * ans % MOD;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}