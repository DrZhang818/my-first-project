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
    vector adj(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    int ans = inf;
    do {
        bool ok = true;
        for(int i = 1; i <= n; i++) {
            if(i == p[i] || i == p[p[i]]) {
                ok = false;
                break;
            }
        }
        if(!ok) continue;
        int cur = m;
        for(int i = 1; i <= n; i++) {
            cur += adj[i][p[i]] ? -1 : 1;
        }
        ans = min(ans, cur);
    } while(next_permutation(p.begin() + 1, p.end()));
    cout << ans << "\n";
}


// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector adj(n + 1, vector<int>(n + 1));
//     for(int i = 1; i <= m; i++) {
//         int u, v;
//         cin >> u >> v;
//         adj[u][v] = adj[v][u] = 1;
//     }
//     vector<int> p(n);
//     iota(p.begin(), p.end(), 1);
//     int ans = inf;
//     do {
//         vector<int> pre(n);
//         for(int i = 0; i < n - 1; i++) {
//             if(adj[p[i]][p[i + 1]]) {
//                 pre[i + 1] = -1;
//             } else {
//                 pre[i + 1] = 1;
//             }
//         }
//         for(int i = 1; i < n; i++) {
//             pre[i] += pre[i - 1];
//         }
//         vector dp(n, vector<int>(n));
//         for(int len = 3; len <= n; len++) {
//             for(int i = 0; i < n; i++) {
//                 int j = i + len - 1;
//                 if(j >= n) break;
//                 dp[i][j] = pre[j] - pre[i] + (adj[p[i]][p[j]] ? -1 : 1);
//                 for(int k = i + 2; k + 2 < j; k++) {
//                     dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
//                 }
//             }
//         }
//         ans = min(ans, m + dp[0][n - 1]);
//     } while(next_permutation(p.begin(), p.end()));
//     cout << ans << "\n";
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
