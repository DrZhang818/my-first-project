#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
    friend bool operator < (const info &a, const info &b) {
        return a.w > b.w;
    }
};
struct node {
    ll s;
    int w, pw;
    vector<int> path;
    friend bool operator < (const node &a, const node &b) {
        if(a.w != b.w) return a.w > b.w;
        return a.path > b.path;
    }
};
struct info2 {
    int v, w;
    ll s;
    friend bool operator < (const info2 &a, const info2 &b) {
        return a.w > b.w;
    }
};
void solve() {
    int n, m, k, st, en;
    cin >> n >> m >> k >> st >> en;
    vector<vector<info>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }
    auto dijk = [&](int x, int y, ll s) -> int {
        priority_queue<info2> q;
        vector<int> vis(n + 1);
        vector<int> dis(n + 1, inf);
        dis[x] = 0;
        q.push({x, 0, s});
        while(!q.empty()) {
            auto [u, w, s] = q.top(); q.pop();
            if(u == y) break;
            if(vis[u]) continue;
            vis[u] = true;
            for(auto [v, nw] : adj[u]) {
                if(s >> v & 1) continue;
                if(dis[u] + nw < dis[v]) {
                    dis[v] = dis[u] + nw;
                    q.push({v, dis[v], s | 1LL << v});
                }  
            } 
        }
        return dis[y];
    };
    priority_queue<node> q2;
    int len = dijk(st, en, 1LL << st);
    if(len == inf) {
        cout << "No\n";
        return;
    }
    q2.push({1LL << st, len, 0, vector<int>{st}});
    vector<int> ans;
    while(!q2.empty()) {
        auto [s, w, pw, path] = q2.top(); q2.pop();
        int u = path.back();
        if(u == en) {
            k--;
            if(k == 0) {
                ans = path;
                break;
            }
            continue;
        }
        for(auto [v, nw] : adj[u]) {
            if(s >> v & 1) continue;
            auto npath = path;
            npath.push_back(v);
            int len = dijk(v, en, s | 1LL << v);
            if(len == inf) continue;
            q2.push({s | 1LL << v, pw + nw + len, pw + nw, npath});
        }
    }
    if(ans.empty()) {
        cout << "No\n";
    } else {
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i] << "-\n"[i == ans.size() - 1];
        }
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
