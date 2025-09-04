#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa, sz, deg;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
    sz[u] += sz[v];
    deg[u] += deg[v];
}
void solve() {
    int n, m;
    cin >> n >> m;
    fa.resize(n + 1);
    sz.resize(n + 1, 1);
    deg.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<PII> e(m + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        e[i] = {u, v};
    }
    for(int i = 1; i <= m; i++) {
        auto [u, v] = e[i];
        merge(u, v);
    }
    ll ans = 0;
    vector<int> tmp;
    for(int i = 1; i <= n; i++) {
        if(find(i) != i) continue;
        ans += 1LL * sz[i] * (sz[i] - 1) / 2 - deg[i] / 2;
        tmp.push_back(sz[i]);
    }
    if(ans) {
        cout << ans << "\n";
        return;
    }
    assert(tmp.size() >= 2);
    sort(tmp.begin(), tmp.end());
    ans = tmp[0] * tmp[1];
    cout << ans << "\n";
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
