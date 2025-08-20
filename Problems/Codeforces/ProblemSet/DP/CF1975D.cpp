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
    int a, b;
    cin >> a >> b;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> fa(n + 1), dep(n + 1);
    auto dfs = [&](this auto &&self, int u, int p) -> void {
        if(p) dep[u] = dep[p] + 1, fa[u] = p;
        for(int v : adj[u]) {
            if(v == p) continue;
            self(v, u);
        }
    };
    dfs(a, 0);
    int c = dep[b] / 2;
    int ans = 0;
    while(dep[b] > c) {
        ans++;
        b = fa[b];        
    }
    for(int i = 1; i <= n; i++) {
        dep[i] = 0;
    }
    dfs(b, 0);
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        mx = max(mx, dep[i]);
    }
    ans += 2 * (n - 1) - mx;
    cout << ans << "\n";
}

// void solve() {
//     int n;
//     cin >> n;
//     int a, b;
//     cin >> a >> b;
//     vector<vector<int>> adj(n + 1);
//     for(int i = 1; i < n; i++) {
//         int u, v;
//         cin >> u >> v;
//         adj[u].push_back(v);
//         adj[v].push_back(u);
//     }
//     vector<int> mx1(n + 1), mx2(n + 1), fa(n + 1), sz(n + 1), son(n + 1), dep(n + 1);
//     mx1[0] = mx2[0] = -inf;
//     vector<int> d(n + 1);
//     auto dfs = [&](this auto &&self, int u, int p) -> void {
//         if(p) d[u] = d[p] + 1;
//         sz[u] = 1;
//         fa[u] = p;
//         dep[u] = dep[p] + 1;
//         for(int v : adj[u]) {
//             if(v == p) continue;
//             self(v, u);
//             sz[u] += sz[v];
//             if(sz[v] > sz[son[u]]) {
//                 son[u] = v;
//             }
//             if(mx1[v] + 1 >= mx1[u]) {
//                 mx2[u] = mx1[u];
//                 mx1[u] = mx1[v] + 1;
//             } else if(mx1[v] + 1 > mx2[u]) {
//                 mx2[u] = mx1[v] + 1;
//             }
//         }
//     };
//     dfs(1, 0);
//     auto dfs2 = [&](this auto &&self, int u, int p) -> void {
//         if(mx1[u] + 1 < mx1[p]) {
//             mx2[u] = mx1[u];
//             mx1[u] = mx1[p] + 1;
//         } else {
//             if(mx1[u] <= mx2[p] + 1) {
//                 mx2[u] = mx1[u];
//                 mx1[u] = mx2[p] + 1;
//             } else {
//                 mx2[u] = max(mx2[u], mx2[p] + 1);
//             }
//         }
//         for(int v : adj[u]) {
//             if(v == p) continue;
//             self(v, u);
//         }
//     };
//     dfs2(1, 0);
//     vector<int> top(n + 1);
//     auto dfs3 = [&](this auto &&self, int u, int t) -> void {
//         top[u] = t;
//         if(!son[u]) return;
//         self(son[u], t);
//         for(int v : adj[u]) {
//             if(v == fa[u] || v == son[u]) continue;
//             self(v, v);
//         }
//     };
//     dfs3(1, 1);
//     auto LCA = [&](int u, int v) -> int {
//         while(top[u] != top[v]) {
//             if(dep[top[u]] < dep[top[v]]) {
//                 swap(u, v);
//             }
//             u = fa[top[u]];
//         }
//         return dep[u] < dep[v] ? u : v;
//     };
//     auto dis = [&](int u, int v) -> int {
//         return d[u] + d[v] - 2 * d[LCA(u, v)];
//     };
//     int ans = inf;
//     for(int i = 1; i <= n; i++) {
//         int d1 = dis(a, i), d2 = dis(b, i);
//         int cur = max(d1, d2);
//         if(d1 > d2 && d1 % 2 != d2 % 2) {
//             cur++;
//         }
//         ans = min(ans, cur + 2 * (n - 1) - mx1[i]);
//     }
//     cout << ans << "\n";
// }

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
