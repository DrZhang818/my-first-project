#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    if(n == 1) {
        cout << 1 << "\n";
        cout << 1 << " " << 0 << "\n";
        return;
    }

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

    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            q.push(i);
        }
    }

    int rem = n;
    int r = 0;

    while(rem > 2) {
        int sz = q.size();
        rem -= sz;
        r++;
        while(sz--) {
            int u = q.front();
            q.pop();
            for(int v : adj[u]) {
                if(--deg[v] == 1) {
                    q.push(v);
                }
            }
        }
    }


    vector<pair<int,int>> ans {};
    if(q.size() == 1) {
        int o = q.front();   
        for(int i = 0; i <= r; i++) {
            ans.emplace_back(o, i);
        }
    } else {
        int x = q.front(); q.pop();
        int y = q.front();
        for(int i = r; i >= 0; i -= 2) {
            ans.emplace_back(x, i);
            ans.emplace_back(y, i);
        }
    }

    cout << ans.size() << "\n";
    for(auto [u, d] : ans) {
        cout << u << " " << d << "\n";
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
