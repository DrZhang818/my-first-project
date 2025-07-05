#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
const ll inf = 1e18;
int n;
void solve() { 
    vector<vector<ll>> dis(n + 1, vector<ll>(n + 1, inf));
    vector<vector<int>> nxt(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> dis[i][j];
            if(dis[i][j] == -1) {
                dis[i][j] = inf;
            } 
            nxt[i][j] = j;
        }
    }
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dis[i][k] >= inf || dis[k][j] >= inf) continue;
                ll &pre = dis[i][j], cur = dis[i][k] + dis[k][j] + a[k];
                if(pre > cur || pre == cur && nxt[i][k] < nxt[i][j]) {
                    pre = cur;
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }
    int u, v;
    while(cin >> u >> v) {
        if(u == -1 && v == -1) break;
        cout << "From " << u << " to " << v << " :\n";
        int s = u;
        cout << "Path: ";
        while(s != v) {
            cout << s << "-->";
            s = nxt[s][v];
        }
        cout << v << "\n";
        cout << "Total cost : " << dis[u][v] << "\n\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n) {
        if(n == 0) break;
        solve();
    }
    return 0;
}
    
