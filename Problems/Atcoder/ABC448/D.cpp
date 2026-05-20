#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> ans(n + 1);
    map<int,int> mp;
    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        ans[u] = ans[fa];
        if(++mp[a[u]] >= 2) {
            ans[u] = 1;
        }
        for(int v : adj[u]) {
            if(v == fa) continue;
            self(v, u);
        }
        mp[a[u]]--;
    };
    dfs(1, 0);
    for(int i = 1; i <= n; i++) {
        if(ans[i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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
