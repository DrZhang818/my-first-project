#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct DSU {
    vector<int> fa;
    vector<int> dis;
    DSU(int n) : fa(n), dis(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int o) {
        if(o != fa[o]) {
            int rt = find(fa[o]);
            dis[o] ^= dis[fa[o]];
            fa[o] = rt;
        }
        return fa[o];
    }
    bool merge(int u, int v, int w) {
        int x = find(u);
        int y = find(v);
        if(x == y) {
            return (dis[u] ^ dis[v]) == w;
        }
        dis[x] = dis[u] ^ dis[v] ^ w;
        fa[x] = y;
        return true;
    }
    pair<int,int> get(int o) {
        int u = find(o);
        return {u, dis[o] ^ dis[fa[o]]};
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n + 1);
    bool ok = true;
    while(m--) {
        int u, v;
        string s;
        cin >> u >> v >> s;
        int op = s[0] == 'i' ? 1 : 0;
        ok &= dsu.merge(u, v, op);
    }
    if(!ok) {
        cout << -1 << "\n";
        return;
    }
    vector<int> tot(n + 1), cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        auto [fa, val] = dsu.get(i);
        tot[fa]++;
        if(val == 1) cnt[fa]++;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += max(cnt[i], tot[i] - cnt[i]);
    }
    cout << ans << "\n";
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
