#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int x, int y) {
    cout << "? " << x << " " << y << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int u) {
    cout << "! " << u << endl;
}

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

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        auto it = find(adj[u].begin(), adj[u].end(), fa);
        if(it != adj[u].end()) {
            swap(adj[u].back(), *it);
            adj[u].pop_back();
        }
        for(int v : adj[u]) {
            self(v, u);
        }
    };
    dfs(1, 0);

    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            q.push(v);
        }
        if(q.empty()) {
            answer(u);
            return;
        }
        int v = q.front();
        q.pop();
        for(int p : adj[v]) {
            q.push(p);
        }
        if(query(u, v)) {
            if(query(u, u)) {
                answer(u);
            } else {
                answer(v);
            }
            return;
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
