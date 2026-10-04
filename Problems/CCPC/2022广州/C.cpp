#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

struct DSU {
    vector<int> fa, sz;
    int cnt;
    DSU(int n) : fa(n), sz(n, 1), cnt(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return;
        cnt--;
        if(sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        fa[v] = u;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    int query() const {
        return cnt - 1;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    const int N = 2 * n;
    DSU dsu(N + 1);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        dsu.merge(n + u, v);
    }

    vector<vector<int>> adj(N + 1);
    vector<int> deg(N + 1);
    for(int i = 1; i <= n; i++) {
        if(dsu.find(i) == dsu.find(n + i)) {
            cout << "No\n";
            return;
        }
        adj[dsu.find(n + i)].push_back(dsu.find(i)); 
        deg[dsu.find(i)]++;
    }

    vector<int> d(N + 1, inf);

    int tot = dsu.query();
    queue<int> q;
    for(int i = 1; i <= N; i++) {
        if(i != dsu.find(i)) continue;
        if(deg[i] == 0) {
            tot--;
            q.push(i);
            d[i] = 0;
        }
    }

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                tot--;
                q.push(v);
            }
            d[v] = min(d[v], d[u] - 1);
        }
    }

    if(tot != 0) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";
    for(int i = 1; i <= n; i++) {
        cout << d[dsu.find(n + i)] - d[dsu.find(i)] << " \n"[i == n];
    }

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
