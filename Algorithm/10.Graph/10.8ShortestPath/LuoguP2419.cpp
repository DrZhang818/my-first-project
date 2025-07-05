#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P2419
void solve() {
    int n, m;
    cin >> n >> m;
    vector<bitset<105>> adj(n + 1);
    for(int i = 1; i <= n; i++) {
        adj[i].set(i);
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].set(v);
    }
    for(int k = 1; k <= n; k++) 
        for(int i = 1; i <= n; i++) 
            if(adj[i][k]) 
                adj[i] |= adj[k];
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int ok = 1;
        for(int j = 1; j <= n; j++) {
            ok &= adj[i][j] | adj[j][i];
        }
        ans += ok;
    }
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
