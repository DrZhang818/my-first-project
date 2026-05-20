#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

struct DSU {
    vector<int> fa;
    vector<int> sz;
    vector<int> dis;
    DSU(int n) : fa(n), sz(n), dis(n) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int o) {
        if(o != fa[o]) {
            int rt = find(fa[o]);
            dis[o] ^= dis[fa[o]];
            fa[o] = rt;
        }
        return fa[o];
    }

    bool merge(int u, int v, int w) {
        int x = find(u);
        int y = find(v);
        if(x == y) {
            return (dis[u] ^ dis[v]) == w;
        }
        fa[x] = y;
        sz[y] += sz[x];
        dis[x] = dis[u] ^ dis[v] ^ w;
        return true;
    }

    int getDis(int o) {
        find(o);
        return dis[o];
    }

    int getSiz(int o) {
        return sz[find(o)];
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<int> deg(n + 1);
    vector<pair<int,int>> edges(n - 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        edges[i - 1] = {u, v};
    }

    DSU dsu(n + 1);
    for(int i = 1; i <= n; i++) {
        if(deg[i] & 1) {
            dsu.sz[i] = 1;
        }
    }

    bool ok = true;
    while(q--) {
        int u, v, x;
        cin >> u >> v >> x;
        if(!dsu.merge(u, v, x)) {
            ok = false;
        }
    }
    if(!ok) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";

    int ans = 0;
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        d[i] = dsu.getDis(i);
        if(deg[i] & 1) {
            ans ^= d[i];
        }
    }

    for(int i = 1; i <= n; i++) {
        if(dsu.getSiz(i) & 1) {
            int rt = dsu.find(i);
            for(int j = 1; j <= n; j++) {
                if(dsu.find(j) == rt) {
                    d[j] ^= ans;
                }
            }
            ans = 0;
            break;
        }
    }

    for(auto [u, v] : edges) {
        cout << (d[u] ^ d[v]) << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}