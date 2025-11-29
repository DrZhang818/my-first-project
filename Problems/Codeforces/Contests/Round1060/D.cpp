#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> d(n + 1);
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        for(int v : adj[u]) {
            if(v == fa) continue;
            d[v] = d[u] + 1;
            self(v, u);
        }
    };
    dfs(n, 0);
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(),
        [&](auto x, auto y) {
            return d[x] > d[y];
        });
    vector<PII> ans;
    int cur = d[1];
    for(int i = 1; i <= n; i++) {
        int x = p[i];
        if(cur % 2 != d[x] % 2) {
            ans.push_back({1, 0});
            cur++;
            ans.push_back({1, 0});
            cur++;
            if(x == n) {
                break;
            }
            ans.push_back({2, x});
        } else {
            ans.push_back({1, 0});
            cur++;
            if(x == n) {
                break;
            }
            ans.push_back({2, x});
        }
    }
    cout << ans.size() << "\n";
    for(auto [p, q] : ans) {
        if(p == 1) {
            cout << 1 << "\n";
        } else {
            cout << p << " " << q << "\n";
        }
    }
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
