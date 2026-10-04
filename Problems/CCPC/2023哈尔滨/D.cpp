#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

int w[N + 1];

struct DSU {
    vector<int> fa, siz;
    DSU(int n) : fa(n), siz(n, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) {
        return o == fa[o] ? fa[o] : fa[o] = find(fa[o]);
    }
    bool merge(int u, int v) {
        u = find(u);
        v = find(v);
        if(u == v) return false;
        if(siz[u] < siz[v]) swap(u, v);
        fa[v] = u;
        siz[u] += siz[v];
        return true;
    }
};

void solve() {
    int l, r;
    cin >> l >> r;

    array<vector<pair<int,int>>, 15> e {};
    for(int d = 1; d <= r; d++) {
        int x = (l + d - 1) / d * d;
        int mn = x;
        for(int y = x; y <= r; y += d) {
            if(w[y] < w[mn]) mn = y;
        }
        for(int y = x; y <= r; y += d) {
            if(y == mn) continue;
            int cur = w[y] + w[mn] - w[gcd(y, mn)];
            e[cur].emplace_back(y, mn);
        }
    }

    DSU dsu(r + 1);
    i64 ans = 0;
    for(int i = 0; i < 15; i++) {
        for(auto& [x, y] : e[i]) {
            if(dsu.merge(x, y)) {
                ans += i;
            }
        }
    }

    cout << ans << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int p = 2; p <= N; p++) {
        if(w[p]) continue;
        for(int i = p; i <= N; i += p) {
            w[i]++;
        }
    }

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
