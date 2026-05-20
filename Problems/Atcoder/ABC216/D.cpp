#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    for(int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        int las = -1;
        for(int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            if(las != -1) {
                adj[las].push_back(x);
                deg[x]++;
            }
            las = x;
        }
    }

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(--deg[v] == 0) {
                q.push(v);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(deg[i] > 0) {
            cout << "No\n";
            return;
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
