#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


struct info {
    int v, tag;
};
void solve() {
    int n;
    cin >> n;
    vector<vector<info>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int sz; cin >> sz;
        a[i].resize(sz + 1);
        for(int j = 1; j <= sz; j++) {
            cin >> a[i][j].v >> a[i][j].tag;
        }
    }
    int ans = 0;
    for(int s = 0; s < (1 << n); s++) {
        bool ok = true;
        vector<bool> tr(n + 1), fal(n + 1);
        int cnt = 0;
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(s >> i & 1) {
                cnt++;
                q.push(i + 1);
            }
        }
        vector<bool> vis(n + 1);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            tr[u] = true;
            vis[u] = true;
            for(info pp : a[u]) {
                int v = pp.v, tag = pp.tag;
                if(tag == 1) {
                    tr[v] = true;
                    if(!vis[v]) q.push(v);
                } else {
                    fal[v] = true;
                }
            }
        }
        
        for(int i = 1; i <= n; i++) {
            if(tr[i] && fal[i]) {
                ok = false;
            }
        }
        if(ok) ans = max(ans, cnt);
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
