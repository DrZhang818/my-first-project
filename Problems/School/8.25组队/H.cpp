#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int cnt, id;
    friend bool operator < (const info &a, const info &b) {
        if(a.cnt != b.cnt) return a.cnt < b.cnt;
        return a.id < b.id;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n + 1, 1), w(n + 1);
    int p = -1;
    auto dfs = [&](auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sz[u] += sz[v];
            w[u] = max(w[u], sz[v]);
        }
        if(max(w[u], n - sz[u]) <= n / 2) {
            p = u; 
        }
    };
    dfs(dfs, 1, 0);
    for(int i = 1; i <= n; i++) {
        sz[i] = 1;
    }
    auto work = [&](auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u);
            sz[u] += sz[v];
        }
    }; 
    work(work, p, 0);
    set<info> st;
    if(n % 2 == 0) {
        st.insert({1, p});
    }
    for(int v : adj[p]) {
        st.insert({sz[v], v});
    }
    vector<vector<int>> point(n + 1);
    for(int v : adj[p]) {
        cerr << sz[v] << " " << point[v].size() << "\n";
    }
    vector<int> pos(n + 1);
    auto dfs2 = [&](auto &&self, int u, int fa, int top) -> void {
        point[top].push_back(u);
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(self, v, u, top);
        }
    };
    for(int v : adj[p]) {
        dfs2(dfs2, v, p, v);
    }
    vector<PII> ans;
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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
