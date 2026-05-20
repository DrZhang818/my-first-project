#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr i64 inf = 1E18;

struct Edge {
    int u, v, w;
};

vector<int> fa;
vector<int> sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    fa[v] = u;
    sz[u] += sz[v];
}

void solve() {
    int n;
    cin >> n;

    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    sz.resize(n + 1, 1);

    vector<Edge> e(n);
    for(int i = 1; i < n; i++) {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }

    sort(e.begin() + 1, e.end(), 
        [&](auto x, auto y) {
            return x.w < y.w;
        });

    i64 ans = 0;

    for(auto [u, v, w] : e) {
        u = find(u);
        v = find(v);
        ans += 1LL * w * sz[u] * sz[v];
        merge(u, v);
    }

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
