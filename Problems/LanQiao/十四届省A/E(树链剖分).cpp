#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int n, cnt[200005], freq[200005], ans = 0;
vector<int> col, son, sz;
vector<vector<int>> adj;
void init() {
    col.resize(n + 1);
    son.resize(n + 1);
    sz.resize(n + 1);
    adj.resize(n + 1);
} 
void dfs(int u, int fa) {
    sz[u] = 1;
    for(int v : adj[u]) {
        dfs(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) {
            son[u] = v;
        }
    }
}
void add(int u, int d) {
    freq[cnt[col[u]]]--;
    cnt[col[u]] += d;
    freq[cnt[col[u]]]++;
    for(int v : adj[u]) {
        add(v, d);
    }
}
void dsu(int u, bool save) {
    for(int v : adj[u]) if(v != son[u]) dsu(v, false);
    if(son[u]) dsu(son[u], true);
    for(int v : adj[u]) if(v != son[u]) add(v, 1);
    freq[cnt[col[u]]]--;
    cnt[col[u]]++;
    freq[cnt[col[u]]]++;
    if(cnt[col[u]] * freq[cnt[col[u]]] == sz[u]) ans++;
    if(!save) add(u, -1);
}
void solve() { 
    cin >> n;
    init();
    for(int i = 1; i <= n; i++) {
        int f;
        cin >> col[i] >> f;
        if(i >= 2) {
            adj[f].push_back(i);
        }
    }
    dfs(1, 0);
    dsu(1, true);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
