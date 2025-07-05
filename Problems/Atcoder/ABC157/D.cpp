#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa, sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
bool same(int u, int v) { return find(u) == find(v); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[u] = v;
    sz[v] += sz[u];
} 
void solve() {
    int n, m, k;
    cin >> n >> m >> k;   
    fa.resize(n + 1);
    sz.resize(n + 1, 1);
    iota(fa.begin(), fa.end(), 0);
    vector<int> deg(n + 1, 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        merge(u, v);
        deg[u]++;
        deg[v]++;
    }
    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        ans[i] = sz[find(i)] - deg[i];
    }
    for(int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        if(same(u, v)) {
            ans[u]--;
            ans[v]--;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
