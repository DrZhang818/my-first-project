#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://acm.hdu.edu.cn/showproblem.php?pid=1704
void solve() {
    int n, m;
    cin >> n >> m;
    vector<bitset<500>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].set(v);
    }
    for(int i = 1; i <= n; i++) {
        adj[i].set(i);
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            if(adj[i][k]) {
                adj[i] |= adj[k];
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            if(adj[i][j] == 0 && adj[j][i] == 0) {
                ans++;
            }
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
