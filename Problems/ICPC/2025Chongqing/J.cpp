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
    string s;
    cin >> s;
    s = "#" + s;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1), tag(n + 1), col(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<int> leaf(n + 1);
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            leaf[i] = 1;
        }
    }

    auto dfs = [&](this auto &&self, int u) -> void {
        tag[u] = 1;
        for(int v : adj[u]) {
            if(tag[v]) {
                continue;
            }
            if(s[v] == s[u]) {
                deg[v]--;
                if(deg[v] == 1) {
                    self(v);
                }
            }
        }
    };

    for(int i = 1; i <= n; i++) {
        if(!tag[i] && leaf[i] == 1) {
            dfs(i);
        }
    }

    int ans = n;
    for(int i = 1; i <= n; i++) {
        if(tag[i]) {
            ans--;
        }
    }
    cout << ans << "\n";
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
