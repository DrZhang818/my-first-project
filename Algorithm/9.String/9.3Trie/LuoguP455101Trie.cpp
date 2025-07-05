#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int v, w;
};
struct node {
    int cnt = 0, son[2];
};
int n;
vector<vector<info>> adj;
vector<int> dist;
void dfs(int u) {
    for(auto [v,w] : adj[u]) {
        dist[v] = dist[u] ^ w;
        dfs(v); 
    }
}
vector<node> tr;
int nxt(int u, int v) {
    if(tr[u].son[v] == 0) {
        tr.push_back(node());
        tr[u].son[v] = tr.size() - 1;
    }
    return tr[u].son[v];    
}
void add(int x) {
    int cur = 0;
    for(int i = 30; i >= 0; i--) {
        int v = (x >> i & 1);
        cur = nxt(cur, v);
        tr[cur].cnt++;
    }
}
int query(int x) {
    int ans = 0, cur = 0;
    for(int i = 30; i >= 0; i--) {
        int v = (x >> i & 1);
        if(tr[cur].son[v ^ 1] != 0) cur = tr[cur].son[v ^ 1], ans += (1 << i);
        else cur = tr[cur].son[v]; 
    }
    return ans;
}
void solve() {
    cin >> n;
    adj.resize(n + 1);
    dist.resize(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }
    dfs(1);
    tr.push_back(node());
    for(int i = 1; i <= n; i++) add(dist[i]);
    int ans = 0;
    for(int i = 1; i <= n; i++) ans = max(ans, query(dist[i]));
    cout << ans << "\n";
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
