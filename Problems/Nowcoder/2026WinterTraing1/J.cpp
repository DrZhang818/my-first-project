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
    int u = -1, v = -1;
    ll w = numeric_limits<ll>::max();
};

void solve() {  
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](auto x, auto y) {
            return a[x] < a[y];
        });
    sort(a.begin() + 1, a.end());
    vector<int> ip(n + 1);
    for(int i = 1; i <= n; i++) {
        ip[p[i]] = i;
    }

    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u = ip[u];
        v = ip[v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    num = n;

    for(int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    ll ans = 0;
    while(num > 1) {
        vector<Edge> mn(n + 1);
        vector<int> roots;

        for(int i = 1; i <= n; i++) {
            if(find(i) == i) {
                roots.push_back(i);
            }
        }

        vector<int> r(n + 1);
        r[n] = n;
        for(int i = n - 1; i >= 1; i--) {
            if(fa[i] == fa[i + 1]) {
                r[i] = r[i + 1];
            } else {
                r[i] = i;
            }
        }

        for(int i = 1; i <= n; i++) {
            int root = fa[i];
            for(int j = 1; j <= n; j++) {
                if(fa[j] == root) {
                    j = r[j];
                    continue;
                }
                auto it = lower_bound(adj[i].begin(), adj[i].end(), j);
                if(it != adj[i].end() && (*it) == j) {
                    continue;
                }
                int w = a[i] + a[j];
                if(w < mn[root].w) {
                    mn[root] = {i, j, w};
                }
                break;
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
        cout << -1 << "\n";
        return;
    }
    cout << ans << "\n";
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
