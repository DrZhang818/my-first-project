#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int u, v, tag;
};
vector<int> fa;
int find(int u) {
    if(u != fa[u]) {
        fa[u] = find(fa[u]);
    }
    return fa[u];
}
bool merge(int u, int v) {
    int fu = find(u);
    int fv = find(v);
    if(fu == fv) return false;
    fa[fu] = fv;
    return true;
}
bool same(int u, int v) {
    return find(u) == find(v);
}
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    vector<int> val;
    for(int i = 1; i <= n; i++) {
        int u, v, tag;
        cin >> u >> v >> tag;
        a[i] = info(u, v, tag);
        val.push_back(u);
        val.push_back(v);
    }    
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int m = val.size();
    fa.assign(m + 5, 0);
    iota(fa.begin(), fa.end(), 0);
    for(int i = 1; i <= n; i++) {
        if(a[i].tag == 1) {
            int u = lower_bound(val.begin(), val.end(), a[i].u) - val.begin() + 1;
            int v = lower_bound(val.begin(), val.end(), a[i].v) - val.begin() + 1;
            merge(u, v);
        }
    }
    bool ok = true;
    for(int i = 1; i <= n; i++) {
        if(a[i].tag == 0) {
            int u = lower_bound(val.begin(), val.end(), a[i].u) - val.begin() + 1;
            int v = lower_bound(val.begin(), val.end(), a[i].v) - val.begin() + 1;
            if(same(u, v)) {
                ok = false;
                break;
            } 
        }
    }
    if(!ok) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
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
    
