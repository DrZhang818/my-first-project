#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct DSU {
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
    bool dif(int u, int v) {
        return find(u) != find(v);
    }
    DSU(int n) {
        fa.assign(n, 0);
        iota(fa.begin(), fa.end(), 0);
    }
};
void solve() { 
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    DSU g1(n + 1), g2(n + 1);
    for(int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        g1.merge(u, v);
    }
    for(int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        g2.merge(u, v);
    }
    vector<PII> ans;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(g1.dif(i, j) && g2.dif(i, j)) {
                g1.merge(i, j);
                g2.merge(i, j);
                ans.push_back({i, j});
            }
        }
    }
    cout << (int)ans.size() << "\n";
    for(auto [u, v] : ans) {
        cout << u << " " << v << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
