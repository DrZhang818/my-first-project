#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    
    vector<vector<int>> A(n + 1, vector<int>(n + 1));
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            cin >> A[i + 1][j + 1];
            A[j + 1][i + 1] = A[i + 1][j + 1];
        }
    }

    vector<vector<pair<int,int>>> adj(n + 1);
    vector<bool> vis(n + 1);
    vis[1] = true;

    auto f = A[1];

    for(int t = 1; t < n; t++) {
        int x = -1;
        for(int i = 1; i <= n; i++) {
            if(!vis[i] && (x == -1 || f[i] < f[x])) {
                x = i;
            }
        }

        for(int i = 1; i <= n; i++) {
            if(vis[i] && f[x] == A[i][x]) {
                adj[i].emplace_back(x, f[x]);
                adj[x].emplace_back(i, f[x]);
                break;
            }
        }
        vis[x] = true;
        for(int i = 1; i <= n; i++) {
            f[i] = min(f[i], A[x][i]);
        }
    }

    vector<int> dis(n + 1);
    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        for(auto [v, w] : adj[u]) {
            if(v == fa) continue;
            dis[v] = dis[u] + w;
            self(v, u);
        }
    };

    for(int u = 1; u <= n; u++) {
        dis.assign(n + 1, 0);
        dfs(u, 0);
        for(int v = u + 1; v <= n; v++) {
            if(dis[v] != A[u][v]) {
                cout << "No\n";
                return;
            }
        }
    }

    cout << "Yes\n";
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
