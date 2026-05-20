#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct DSU { 
    vector<int> fa;
    vector<int> dis;
    vector<array<int, 2>> dp;
    DSU(int n) : fa(n), dis(n), dp(n, {1, 0}) {
        iota(fa.begin(), fa.end(), 0);
    }
    auto find(int o) -> int {
        if(o != fa[o]) {
            int rt = find(fa[o]);
            dis[o] ^= dis[fa[o]];
            fa[o] = rt;
        }
        return fa[o];
    }
    auto merge(int u, int v) {
        int x = find(u);
        int y = find(v);
        if(x == y) return (dis[u] ^ dis[v]) == 1 ? 0 : -inf;
        fa[x] = y;
        dis[x] = dis[u] ^ dis[v] ^ 1;
        int pre = min(dp[x][0], dp[x][1]) + min(dp[y][0], dp[y][1]);
        dp[y][0] += dp[x][dis[x]];
        dp[y][1] += dp[x][dis[x] ^ 1];
        return min(dp[y][0], dp[y][1]) - pre;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    DSU dsu(n + 1);

    int ans = 0;
    while(q--) {
        int u, v;
        cin >> u >> v;
        if(ans == -1) {
            cout << -1 << "\n";
            continue;
        }
        int res = dsu.merge(u, v);
        if(res == -inf) {
            ans = -1;
        } else {
            ans += res;
        }
        cout << ans << "\n";
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
