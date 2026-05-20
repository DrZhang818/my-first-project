#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    array<int, 30> basis {};

    auto add_basis = [&](int x) {
        for(int i = 29; i >= 0; i--) {
            if(x >> i & 1) {
                if(!basis[i]) {
                    basis[i] = x;
                    return;
                }
                x ^= basis[i];
            }
        }
    };

    vector<int> dis(n + 1, -1);
    dis[1] = 0;

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            if(dis[v] != -1) {
                add_basis(dis[u] ^ dis[v] ^ w);
            } else {
                dis[v] = dis[u] ^ w;
                self(v, u);
            }
        }
    };
    dfs(1, 0);

    auto reduce = [&](int x) {
        for(int i = 29; i >= 0; i--) {
            x = min(x, x ^ basis[i]);
        }
        return x;
    };

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = reduce(dis[i]);
    }

    vector<array<int, 2>> tr {};
    vector<int> cnt;
    auto add = [&]() {
        tr.push_back({0, 0});
        cnt.push_back(0);
        return tr.size() - 1;
    };

    int rt = add();
    auto insert = [&](int x) {
        int cur = rt;
        for(int i = 29; i >= 0; i--) {
            int s = x >> i & 1;
            if(!tr[cur][s]) {
                tr[cur][s] = add();
            }
            cur = tr[cur][s];
            cnt[cur]++;
        }
    };

    auto query = [&](int x, int lim) {
        int cur = rt;
        i64 res = 0;
        for(int i = 29; i >= 0; i--) {
            int s = x >> i & 1;
            int t = lim >> i & 1;
            if(t) {
                res += cnt[tr[cur][s]];
                cur = tr[cur][s ^ 1];
            } else {
                cur = tr[cur][s];
            }
            if(cur == 0) break;
        }
        res += cnt[cur];
        return res;
    };

    i64 ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += query(a[i], k);
        insert(a[i]);
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
