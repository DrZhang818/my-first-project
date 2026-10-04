#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

struct DSU {
    int len;
    i64 mx;
    vector<int> fa, sz, to;
    vector<i64> d;
    DSU(int n) : len(0), mx(0), fa(n), d(n), sz(n), to(n) {
        iota(fa.begin(), fa.end(), 0);
        iota(to.begin(), to.end(), 0);
    }
    int find(int o) {
        while(o != fa[o]) {
            fa[o] = fa[fa[o]];
            o = fa[o];
        }
        return o;
    }
    void append(int i, i64 v) {
        len = i;
        d[i] = max(0LL, v - mx);
        mx += d[i];
    }
    void add(int l, i64 v) {
        int a = find(l + 1);
        while(to[a] <= len && d[to[a]] <= v) {
            v -= d[to[a]];

            int b = find(to[a] + 1);
            if(sz[a] < sz[b]) {
                swap(a, b);
            }
            sz[a] += sz[b];
            fa[b] = a;
            to[a] = max(to[a], to[b]);
        }
        if(to[a] <= len) {
            d[to[a]] -= v;
        } else {
            mx += v;
        }
    }
    i64 query() {
        return mx;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int l, r, v;
        cin >> l >> r >> v;
        adj[r].emplace_back(l, v);
    }

    vector<i64> ans(n + 1);

    vector<i64> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        for(auto& [_, v] : adj[i]) {
            dp[i] += v;
        }
    }
    ans[n] = dp[n];

    // ndp[i] = max(dp[j-1] + w(j,i))
    for(int t = 1; t < n; t++) {
        vector<i64> ndp(n + 1);
        DSU dsu(n + 5);
        for(int i = t; i <= n; i++) {
            dsu.append(i, dp[i - 1]);
            for(auto& [l, v] : adj[i]) {
                if(l < t) continue;
                dsu.add(l, v);
            }
            ndp[i] = dsu.query();
        }
        dp = move(ndp);
        ans[n - t] = dp[n];
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}