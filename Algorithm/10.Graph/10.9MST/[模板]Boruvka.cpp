#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
int num;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
bool merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return false;
    fa[v] = u;
    num--;
    return true;
}

struct Edge {
    int u = -1;
    int v = -1;
    int w = numeric_limits<int>::max();
};

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<PII>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }        

    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    num = n;

    ll ans = 0;

    while(num > 1) {
        vector<Edge> mn(n + 1);
        vector<int> roots;

        for(int i = 1; i <= n; i++) {
            if(find(i) == i) {
                roots.push_back(i);
            }
        }

        for(int i = 1; i <= n; i++) {
            int root = find(i);
            for(auto [v, w] : adj[i]) {
                if(find(v) == root) continue;
                if(w < mn[root].w) {
                    mn[root] = {i, v, w};
                }
            }
        }

        bool change = false;
        for(int i : roots) {
            if(mn[i].u != -1 && merge(mn[i].u, mn[i].v)) {
                ans += mn[i].w;
                change = true;
            }
        }
        if(!change) {
            break;
        }
    }

    if(num > 1) {
        cout << "orz\n";
        return;
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
