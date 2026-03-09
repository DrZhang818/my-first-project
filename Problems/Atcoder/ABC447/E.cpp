#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;
constexpr int N = 200005;

int power2[N + 1];

struct Edge {
    int u, v;
};

struct DSU {
    int n;
    int cnt;
    vector<int> fa;
    DSU(int n) : n(n), cnt(n), fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) {
            return false;
        }
        fa[v] = u;
        cnt--;
        return true;
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    int components() {
        return cnt - 1;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
    } 

    auto ck = [&](int x) -> bool {
        DSU g(n + 1);
        for(int i = x; i <= m; i++) {
            g.merge(edges[i].u, edges[i].v);
        }
        return g.components() >= 2;
    };

    int l = 0, r = m + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    DSU g(n + 1);

    int ans = (power2[r] - 1 + MOD) % MOD;
    for(int i = r; i <= m; i++) {
        g.merge(edges[i].u, edges[i].v);
    }

    for(int i = r - 1; i >= 0; i--) {
        if(g.same(edges[i].u, edges[i].v)) {
            ans = (ans - power2[i] + MOD) % MOD;
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    power2[0] = 1;
    for(int i = 1; i <= N; i++) {
        power2[i] = power2[i - 1] * 2LL % MOD;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
