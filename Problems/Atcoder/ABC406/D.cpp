#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> x(n + 1), y(m + 1);
    for(int i = 1; i <= k; i++) {
        int u, v;
        cin >> u >> v;
        x[u].push_back(i);
        y[v].push_back(i);
    }
    vector<bool> vis(k + 1), vx(n + 1), vy(m + 1);
    int q;
    cin >> q;
    while(q--) {
        int ans = 0, flag, u;
        cin >> flag >> u;
        if(flag == 1) {
            if(vx[u]) {
                cout << 0 << "\n";
                continue;
            }
            vx[u] = true;
            for(int i : x[u]) {
                if(!vis[i]) {
                    ans++;
                    vis[i] = true;
                }
            }
        } else {
            if(vy[u]) {
                cout << 0 << "\n";
                continue;
            }
            vy[u] = true;
            for(int i : y[u]) {
                if(!vis[i]) {
                    ans++;
                    vis[i] = true;
                }
            }
        }     
        cout << ans << "\n";
    }
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
