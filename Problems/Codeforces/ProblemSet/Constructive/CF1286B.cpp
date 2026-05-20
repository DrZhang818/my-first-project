#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> cnt(n + 1);
    int rt = -1;
    for(int i = 1; i <= n; i++) {
        int p;
        cin >> p >> cnt[i];
        if(p) adj[p].push_back(i);
        else rt = i;
    }

    vector<int> sz(n + 1);
    [&](this auto&& self, int u) -> void {
        sz[u] = 1;
        for(int v : adj[u]) {
            self(v);
            sz[u] += sz[v];
        }
    }(rt);
    for(int i = 1; i <= n; i++) {
        if(cnt[i] >= sz[i]) {
            cout << "NO\n";
            return;
        }
    }

    auto dfs = [&](this auto&& self, int u) -> vector<int> {
        vector<int> res;
        for(int v : adj[u]) {
            auto vec = self(v);
            res.insert(res.end(), vec.begin(), vec.end());
        }
        res.insert(res.begin() + cnt[u], u);
        return res;
    };
    auto vec = dfs(rt);

    cout << "YES\n";
    vector<int> ans(n + 1);
    for(int i = 0; i < vec.size(); i++) {
        ans[vec[i]] = i + 1;
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
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