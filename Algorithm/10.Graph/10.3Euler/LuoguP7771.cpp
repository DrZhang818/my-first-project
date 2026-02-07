#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> in(n + 1), out(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        out[u]++;
        in[v]++;
    }

    int S = -1, T = -1;
    bool ok = true;
    int cnt1 = 0, cnt2 = 0;

    for(int u = 1; u <= n; u++) {
        if(in[u] != out[u]) {
            if(out[u] == in[u] + 1) {
                S = u;
                cnt1++;
            } else if(in[u] == out[u] + 1) {
                T = u;
                cnt2++;
            } else {
                ok = false;
                break;
            }
        }
    }

    if(cnt1 > 1 || cnt1 != cnt2) {
        ok = false;
    }

    if(!ok) {
        cout << "No\n";
        return;
    }

    if(S == -1) {
        S = 1;
        for(int u = 1; u <= n; u++) {
            if(out[u] > 0) {
                S = u;
                break;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<int> ans;
    vector<int> cur(n + 1);

    auto euler = [&](auto&& self, int u) -> void {
        while(cur[u] < adj[u].size()) {
            int v = adj[u][cur[u]++];
            self(self, v);
        }
        ans.push_back(u);
    };

    euler(euler, S);
    reverse(ans.begin(), ans.end());

    if(ans.size() != m + 1) {
        cout << "No\n";
        return;
    }

    for(int i = 0; i <= m; i++) {
        cout << ans[i] << " \n"[i == m];
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
