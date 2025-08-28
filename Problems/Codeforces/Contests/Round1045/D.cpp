#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

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
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        if(adj[i].size() > 2) {
            ok = false;
            break;
        }
    }
    if(ok) {
        cout << -1 << "\n";
        return;
    }
    int mx = 0, x = 1, y;
    vector<int> p(n + 1), son(n + 1), dep(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa, int d, int &o) -> void {
        p[u] = fa;
        dep[u] = d;
        if(d > mx) {
            mx = d;
            o = u;
        }
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u, d + 1, o);
        }
    };
    dfs(1, 0, 0, x);
    mx = 0, y = x;
    dfs(x, 0, 0, y);
    vector<PII> point;
    point.push_back({y, dep[y]});
    int pre = 0;
    for(int o = y; o; o = p[o]) {
        son[o] = pre;
        if(adj[o].size() >= 3) {
            point.push_back({o, dep[o]});
        }
        pre = o;
    }
    point.push_back({x, dep[x]});

    int sz = point.size();
    int mn = point[1].second;
    for(int i = 1; i < sz - 1; i++) {
        if(dep[y] - point[i].second + point[i + 1].second <= mn) {
            mn = dep[y] - point[i].second + point[i + 1].second;
        }
    }
    if(point[1].second == mn) {
        int o = point[1].first;
        cout << son[o] << " " << o << " " << p[o] << "\n";
        return;
    }
    for(int i = 1; i < sz - 1; i++) {
        if(dep[y] - point[i].second + point[i + 1].second == mn) {
            int o = point[i].first;
            cout << p[o] << " " << o << " " << son[o] << "\n";
            return;
        }
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
