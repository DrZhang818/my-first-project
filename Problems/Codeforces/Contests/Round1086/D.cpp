#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct DSU {
    int n;
    vector<int> fa;
    DSU(int n) : n(n), fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }
    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        fa[v] = u;
        return true;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
};

void solve() {
    int n;
    cin >> n;

    vector<string> s(n);
    vector<int> deg(n);
    for(int i = 0; i < n; i++) {
        cin >> s[i];
        for(int j = 0; j < n; j++) {
            if(s[i][j] == '1') {
                deg[i]++;
            }
        }
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(),
        [&](int x, int y) {
            return deg[x] > deg[y];
        });

    vector<pair<int,int>> ans;
    vector<vector<int>> adj(n);
    vector<int> covered(n, -1);
    DSU g(n);

    for(int u = 0; u < n; u++) {
        for(int v : p) {
            if(u != v && s[u][v] == '1' && covered[v] != u) {
                ans.emplace_back(u, v);
                adj[u].push_back(v);
                if(ans.size() >= n || !g.merge(u, v)) {
                    cout << "No\n";
                    return;
                }
                for(int w = 0; w < n; w++) {
                    if(s[v][w] == '1') {
                        covered[w] = u;
                    }
                }
            }
        }
    }

    if(ans.size() != n - 1) {
        cout << "No\n";
        return;
    }

    vector<int> vis(n, -1);
    queue<int> q;
    for(int i = 0; i < n; i++) {
        q.push(i);
        vis[i] = i;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v : adj[u]) {
                if(vis[v] != i) {
                    vis[v] = i;
                    q.push(v);
                }
            }
        }
        for(int j = 0; j < n; j++) {
            if((s[i][j] == '1') != (vis[j] == i)) {
                cout << "No\n";
                return;
            }
        }
    }

    cout << "Yes\n";
    for(auto [u, v] : ans) {
        cout << u + 1 << " " << v + 1 << "\n";
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
