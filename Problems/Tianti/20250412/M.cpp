#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n, m, st, en;
struct info {
    int v, w;
};
struct node {
    int u, w, mx;
    friend bool operator < (const node &a, const node &b) {
        if(a.w != b.w) return a.w > b.w;
        return a.mx > b.mx;
    }
};
vector<vector<info>> adj;
const int inf = 1000000000;
void solve() { 
    cin >> n >> m >> st >> en;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    adj.resize(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    priority_queue<node> q;
    vector<bool> vis(n + 1);
    vector<int> d(n + 1, inf), m(n + 1, inf);
    d[st] = 0;
    q.push({st, 0, 0});
    while(!q.empty()) {
        node cur = q.top(); q.pop();
        int u = cur.u, w = cur.w, mx = cur.mx;
        if(vis[u]) continue;
        for(info ifo : adj[u]) {
            int v = ifo.v, nw = ifo.w, nmx = max(mx, a[v]);
            if(v == en) {
                if(d[u] + nw < d[v]) {
                    d[v] = d[u] + nw;
                    m[v] = mx;
                } else if(d[u] + nw == d[v] && mx < m[v]) {
                    m[v] = mx;
                }
                continue;
            }
            if(d[u] + nw < d[v]) {
                d[v] = d[u] + nw;
                m[v] = nmx;
                q.push({v, d[v], nmx});
            } else if(d[u] + nw == d[v] && nmx < m[v]) {
                m[v] = nmx;
                q.push({v, d[v], nmx});
            }
        }
    }
    if(d[en] == inf) {
        cout << "Impossible\n";
    } else {
        cout << d[en] << " " << m[en] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
