#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

class DSU {
public:
    vector<int> parent, size;
    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] > size[rootY]) {
                swap(rootX, rootY);
            }
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
    }
    int getsize(int n) {
        set<int> uniqueRoots;
        for (int i = 1; i <= n; i++) {
            uniqueRoots.insert(find(i));
        }
        return uniqueRoots.size();
    }
};

void solve(){
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    DSU dsu1(n), dsu2(n);
    vector<PII> adj1(m1), adj2(m2);
    for(int i = 0; i < m1; i++){
        int u, v;
        cin >> u >> v;
        adj1[i] = {u, v};
        dsu1.unite(u, v);
    }
    for(int i = 0; i < m2; i++){
        int u, v;
        cin >> u >> v;
        adj2[i] = {u, v};
        dsu2.unite(u, v);
    }
    ll ans = 0;
    vector<PII> adj11;
    for(auto &[u, v] : adj1){
        if(dsu2.find(u) != dsu2.find(v)){
            ans++;
        }else{
            adj11.push_back({u, v});
        }
    }
    DSU dsu3(n);
    for(auto &[u, v] : adj11){
        dsu3.unite(u, v);
    }
    ans += dsu3.getsize(n) - dsu2.getsize(n);
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}