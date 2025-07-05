#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 2E9;

struct edge {
    int u, v, w;
    friend bool operator < (const edge &a, const edge &b) {
        return a.w < b.w;
    }
};
vector<int> fa, mn;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v, int w) {
    u = find(u), v = find(v);
    mn[v] = min({mn[u], mn[v], w});
    if(u == v) return;
    fa[u] = v;
}
bool same(int u, int v) {
    return find(u) == find(v);
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.assign(n + 1, 0);
    mn.assign(n + 1, inf);
    iota(fa.begin(), fa.end(), 0);
    vector<edge> e(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    sort(e.begin(), e.end());
    int ans = inf;
    for(int i = 1; i <= m; i++) {
        auto [u, v, w] = e[i];
        merge(u, v, w);
        if(same(1, n)) {
            ans = min(ans, w + mn[find(1)]);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
