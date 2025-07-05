#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
struct info {
    int u, v, id;
};
int n, q;
vector<vector<int>> adj;
vector<vector<info>> Q;
vector<int> ans, fa, sz;
void init() {
    adj.resize(n + 1);
    Q.resize(n + 1);
    ans.resize(q + 1);
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    sz.resize(n + 1, 1);
}
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
void dfs(int u, int f) {
    unordered_set<int> st;
    for(int v : adj[u]) {
        if(v == f) continue;
        dfs(v, u);
        sz[u] += sz[v];
        st.insert(v);
    }
    for(auto [x, y, id] : Q[u]) {
        if(u == x && u == y) {
            ans[id] = n;
            continue;
        }
        int fx = find(x), fy = find(y);
        if(u == x) {
            if(st.count(fy)) {
                ans[id] = n - sz[fy];
            } else {
                ans[id] = sz[u];
            }
            continue;
        } else if(u == y) {
            if(st.count(fx)) {
                ans[id] = n - sz[fx];
            } else {
                ans[id] = sz[u];
            }
            continue;
        }
        if(fx == fy || !st.count(fx) && !st.count(fy)) {
            ans[id] = 0;
            continue;
        }
        int cnt = n, c = 0;
        if(st.count(fx)) cnt -= sz[fx], c++;
        if(st.count(fy)) cnt -= sz[fy], c++;
        if(c < 2) cnt -= n - sz[u];  
        ans[id] = cnt;   
    }
    for(int v : adj[u]) {
        if(v == f) continue;
        fa[v] = u;
    }
}
void solve() { 
    cin >> n >> q;
    init();
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i <= q; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        Q[c].push_back({u, v, i});
    }
    dfs(1, 0);
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
