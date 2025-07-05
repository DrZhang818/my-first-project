#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;


void solve(){
    int b, n, m, q;
    cin >> b >> n >> m >> q;
    vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, inf));
    vector<vector<int>> val(n + 1, vector<int>(n + 1, -1));
    for(int i = 1; i <= n; i++) dist[i][i] = val[i][i] = 0;
    for(int i = 1; i <= m; i++) {
        int u, v, w, p;
        cin >> u >> v >> w >> p;
        dist[u][v] = dist[v][u] = w;
        val[u][v] = val[v][u] = p;
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dist[i][k] == inf || dist[k][j] == inf) continue;
                ll nd = dist[i][k] + dist[k][j];
                int nv = val[i][k] + val[k][j];
                if(nd < dist[i][j]) dist[i][j] = nd, val[i][j] = nv;
                else if(nd == dist[i][j] && nv > val[i][j]) val[i][j] = nv;
            }
        }
    }
    cerr << dist[1][3] << " : " << val[1][3] << "\n";
    while(q--) {
        int u; cin >> u;
        vector<int> a;
        for(int v = 1; v <= n; v++) if(v != u && dist[u][v] <= b) a.push_back(v);  
        if(a.empty()) { cout << "T_T\n"; continue; }
        for(int i = 0; i < a.size(); i++) cout << a[i] << (i == a.size() - 1 ? "\n" : " ");
        int mx = -1;
        vector<int> vec;
        for(int v : a) mx = max(mx, val[u][v]);
        for(int v : a) if(val[u][v] == mx) vec.push_back(v);
        for(int i = 0; i < vec.size(); i++) cout << vec[i] << (i == vec.size() - 1 ? "\n" : " ");            
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
