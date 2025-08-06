#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//优化解法
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]--;
    }
    string s(n, '0');
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        if(a[u] == a[v]) {
            s[a[u]] = '1';
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(n + 1);
    for(int u = 1; u <= n; u++) {
        for(int v : adj[u]) {
            int x = a[v];
            if(vis[x] == u) {
                s[x] = '1';
            }
            vis[x] = u;
        }
    }
    cout << s << "\n";
}

// void solve() {
//     int n;
//     cin >> n;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     string s(n, '0');
//     vector<map<int,int>> mp(n + 1);
//     for(int i = 1; i < n; i++) {
//         int u, v;
//         cin >> u >> v;
//         mp[u][a[v]]++;
//         mp[v][a[u]]++;
//     }
//     for(int i = 1; i <= n; i++) {
//         if(mp[i][a[i]]) s[a[i] - 1] = '1';
//         for(auto [v, c] : mp[i]) {
//             if(c >= 2) {
//                 s[v - 1] = '1';
//             }
//         }
//     }
//     cout << s << "\n";
// }   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
