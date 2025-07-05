#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P5905
struct info {
    int v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        adj[0].emplace_back(i, 0);
    }
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    queue<int> q;
    vector<int> H(n + 1, inf), vis(n + 1), cnt(n + 1);
    q.push(0); H[0] = 0; vis[0] = true;
    bool ne_circle = false;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(auto [v, w] : adj[u]) {
            if(H[v] > H[u] + w) {
                H[v] = H[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n + 1) {
                    ne_circle = true;
                    break;
                }
                if(!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
        if(ne_circle) {
            break;
        }
    }
    if(ne_circle) {
        cout << -1 << "\n";
        return;
    }
    auto dijk = [&](int st) -> vector<int> {
        vector<int> d(n + 1, inf), vis(n + 1);
        d[st] = 0;
        priority_queue<info> pq;
        pq.push({st, 0});
        while(!pq.empty()) {
            auto [u, _] = pq.top(); pq.pop();
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v, w] : adj[u]) {
                w += H[u] - H[v];
                if(d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    pq.push({v, d[v]});
                }
            }
        }
        return d;
    };
    for(int i = 1; i <= n; i++) {
        ll ans = 0;
        auto d = dijk(i);
        for(ll j = 1; j <= n; j++) {
            if(j == i) continue;
            if(d[j] >= inf) ans += j * inf;
            else ans += j * (d[j] - H[i] + H[j]);
        }
        cout << ans << "\n";
    }

}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
