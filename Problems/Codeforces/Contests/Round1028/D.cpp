#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2116/problem/D

//优化解法(jiangly)
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    vector<array<int,3>> op(q + 1);
    vector<int> u(n + q + 1), v(n + q + 1);
    for(int i = 1; i <= q; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        op[i] = {x, y, z};
        u[n + i] = p[x];
        v[n + i] = p[y];
        p[z] = n + i;
    }
    vector<int> val(n + q + 1);
    for(int i = 1; i <= n; i++) {
        val[p[i]] = b[i];
    }
    for(int i = n + q; i > n; i--) {    
        val[u[i]] = max(val[u[i]], val[i]);
        val[v[i]] = max(val[v[i]], val[i]);
    }
    val.resize(n + 1);
    auto a = val;
    for(int i = 1; i <= q; i++) {
        auto [x, y, z] = op[i];
        a[z] = min(a[x], a[y]);
    }
    if(a != b) {
        cout << -1 << "\n";
        return;
    }
    for(int i = 1; i <= n; i++) {
        cout << val[i] << " \n"[i == n];
    }
}




// struct info {
//     int x, y, z;
// };
// void solve() {
//     int n, q;
//     cin >> n >> q;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }        
//     vector<info> Q(q + 1);
//     for(int i = 1; i <= q; i++) {
//         cin >> Q[i].x >> Q[i].y >> Q[i].z;
//     }
//     vector<bool> vis(n + 1, false);
//     auto ans = a;
//     for(int i = q; i >= 1; i--) {
//         auto [x, y, z] = Q[i];
//         if(z != x && z != y) {
//             if(!vis[z]) {
//                 if(ans[x] > ans[z] && ans[y] > ans[z]) {
//                     cout << -1 << "\n";
//                     return;
//                 }
//             }
//             if(!vis[x] && ans[x] < ans[z] || !vis[y] && ans[y] < ans[z]) {
//                 cout << -1 << "\n";
//                 return;
//             }
//             if(vis[x]) {
//                 ans[x] = max(ans[x], ans[z]);
//             }
//             if(vis[y]) {
//                 ans[y] = max(ans[y], ans[z]);
//             }
//             vis[z] = true;
//             ans[z] = 1;
//         } else if(x != y) {
//             if(z == y) swap(x, y);
//             if(!vis[y] && ans[y] < ans[x]) {
//                 cout << -1 << "\n";
//                 return; 
//             } else {
//                 if(vis[y]) {
//                     ans[y] = max(ans[y], ans[x]);
//                 }
//                 vis[x] = true;
//             }
//         }
//     }
//     auto b = ans;
//     for(int i = 1; i <= q; i++) {
//         auto [x, y, z] = Q[i];
//         b[z] = min(b[x], b[y]);
//     }
//     if(b == a) {
//         for(int i = 1; i <= n; i++) {
//             cout << ans[i] << " \n"[i == n];
//         }
//     } else {
//         cout << -1 << "\n";
//     }
// }

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
