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
    vector<int> deg(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    if(n == 2) {
        cout << 0 << "\n";
        return;
    }
    int cnt = 0, mx = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            cnt++;
        }
        int c = 0;
        for(int j : adj[i]) {
            if(deg[j] == 1) {
                c++;
            }
        }
        mx = max(mx, c);
    }
    cout << cnt - mx << "\n";
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
