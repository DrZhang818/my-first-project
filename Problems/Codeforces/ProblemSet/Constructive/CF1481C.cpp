#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1), c(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> c[i];
    }
    vector<vector<int>> adj(n + 1);
    vector<int> ans(m + 1), idx(n + 1), t;
    for(int i = 1; i <= n; i++) {
        if(a[i] != b[i]) {
            adj[b[i]].push_back(i);
        }
        idx[b[i]] = i;
    }
    for(int i = m; i >= 1; i--) {
        if(adj[c[i]].empty()) {
            if(!idx[c[i]] && t.empty()) {
                cout << "NO\n";
                return;
            } else {
                if(idx[c[i]]) {
                    ans[i] = idx[c[i]];
                    t.push_back(idx[c[i]]);
                } else {
                    ans[i] = t[0];
                }
            }
        } else {
            ans[i] = adj[c[i]].back();
            t.push_back(adj[c[i]].back());
            adj[c[i]].pop_back();
        }
    }
    for(int i = 1; i <= n; i++) {
        if(!adj[i].empty()) {
            cout << "NO\n";
            return;
        }
    }   
    cout << "YES\n";
    for(int i = 1; i <= m; i++) {
        cout << ans[i] << " \n"[i == m];
    }
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
