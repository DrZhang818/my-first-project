#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll cnt;
vector<int> fa, sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) { 
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[u] = v;
    cnt -= 1LL * sz[u] * sz[v];
    sz[v] += sz[u];
}
void solve() {
    int n, m;
    cin >> n >> m;
    cnt = 1LL * n * (n - 1) / 2;
    fa.assign(n + 1, 0);
    sz.assign(n + 1, 1);
    iota(fa.begin(), fa.end(), 0);
    vector<PII> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<ll> ans(m + 1);
    for(int i = m; i >= 1; i--) {
        ans[i] = cnt;
        merge(a[i].first, a[i].second);
    }
    for(int i = 1; i <= m; i++) {
        cout << ans[i] << "\n";
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
