#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    vector<vector<int>> adj1(n + 1), adj2(m + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    for(int i = 1; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }

    if(a[1] != b[1]) {
        cout << 0 << "\n";
        return;
    }

    vector<map<int,int>> mp(n + 1);

    auto dfs = [&](auto&& self, int u, int p) -> void {
        for(int v : adj1[u]) {
            if(v == p) continue;
            mp[u][a[v]] = v;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);

    auto work = [&](auto&& self, int u, int fa, int cur) -> int {
        int res = 1;
        for(int v : adj2[u]) {
            if(v == fa) continue;
            int x = b[v];
            auto it = mp[u].find(x);
            if(it == mp[u].end()) {
                continue;
            }
            int nxt = it->second;
            res = max(res, self(self, v, u, nxt) + 1);
        }
        return res;
    };
    int ans = work(work, 1, 0, 1);

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}