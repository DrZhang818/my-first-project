#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


vector<int> fa, sz;
int find(int u) { return u == fa[u] ? fa[u] : fa[u] = find(fa[u]); }
bool merge(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if(fu == fv) return false;
    fa[fu] = fv;
    sz[fv] += sz[fu];
    return true;
}

void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fa.assign(n + 1, 0);
    sz.assign(n + 1, 1);
    iota(fa.begin(), fa.end(), 0);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        merge(a[i], i);
    }
    vector<int> vis(n + 1);
    int cur = 0;
    int q = n;
    while(q--) {
        int x; 
        cin >> x;
        int fx = find(x);
        if(!vis[fx]) cur += sz[fx];
        vis[fx] = true;
        cout << cur << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
