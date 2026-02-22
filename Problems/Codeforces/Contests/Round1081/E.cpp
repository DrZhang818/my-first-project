#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    using pii = pair<int,int>;
    vector<vector<pii>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        adj[a[i]].emplace_back(b[i], i);
        adj[b[i]].emplace_back(a[i], i);
    }

    for(int i = 1; i <= n; i++) {
        if(int(adj[i].size()) & 1) {
            cout << -1 << "\n";
            return;
        }
    }

    vector<int> cur(n + 1);
    vector<bool> swapped(n + 1);
    vector<bool> used(n + 1);

    int cnt = 0;
    auto dfs = [&](this auto&& self, int u) -> void {
        while(cur[u] < adj[u].size()) {
            auto [v, id] = adj[u][cur[u]++];
            if(used[id]) {
                continue;
            }
            if(u == a[id]) {
                swapped[id] = 0;
            } else {
                swapped[id] = 1;
                cnt++;
            }
            used[id] = true;
            self(v);
        }
    };

    for(int i = 1; i <= n; i++) {
        if(!used[i]) {
            dfs(a[i]);
        }
    }

    cout << cnt << "\n";
    for(int i = 1; i <= n; i++) {
        if(swapped[i]) {
            cout << i << " ";
        }
    }
    cout << "\n";
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
