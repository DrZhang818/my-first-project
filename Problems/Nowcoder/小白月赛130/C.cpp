#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> m >> n;

    vector<int> deg(n + 1);
    vector<pair<int,int>> edges;

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
        if(u > v) swap(u, v);
        edges.emplace_back(u, v);
    }  
    sort(edges.begin(), edges.end());

    int mx1 = 0, mx2 = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] > mx1) {
            mx2 = mx1;
            mx1 = deg[i];
        } else if(deg[i] > mx2) {
            mx2 = deg[i];
        }
    }

    i64 cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == mx2) {
            cnt++;
        }
    }
    if(mx1 == mx2) {
        cnt = 1LL * cnt * (cnt - 1) / 2;
    }
    int mn = inf;
    for(int i = 0, j = 0; i < edges.size(); i = j) {
        while(j < edges.size() && edges[j] == edges[i]) {
            j++;
        }
        auto [u, v] = edges[i];
        if(min(deg[u], deg[v]) == mx2 && max(deg[u], deg[v]) == mx1) {
            mn = min(mn, j - i);
            cnt--;
        }
    }
    if(cnt > 0) {
        mn = 0;
    }

    cout << mx1 + mx2 - mn << "\n";
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
