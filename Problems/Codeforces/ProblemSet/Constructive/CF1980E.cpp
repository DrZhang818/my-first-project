#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//优化解法(jiangly)
void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<int>(m + 1));
    vector<int> r(n * m + 1), c(n * m + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            r[a[i][j]] = i;
            c[a[i][j]] = j;
        }
    }
    vector b(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> b[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        int x = r[b[i][1]];
        swap(a[i], a[x]);
        for(int j = 1; j <= m; j++) {
            r[a[i][j]] = i;
            r[a[x][j]] = x;
        }
    }
    for(int j = 1; j <= m; j++) {
        int x = c[b[1][j]];
        for(int i = 1; i <= n; i++) {
            swap(a[i][j], a[i][x]);
            c[a[i][j]] = j;
            c[a[i][x]] = x;
        }
    }
    if(a == b) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}



// void solve() {
//     int n, m;
//     cin >> n >> m;
//     vector a(n + 1, vector<int>(m + 1)), b(n + 1, vector<int>(m + 1));
//     int c1 = 0;
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             cin >> a[i][j];
//             if(a[i][j] == 1) c1 = j;
//         }
//     }
//     if(c1 != 1) {
//         for(int i = 1; i <= n; i++) {
//             swap(a[i][1], a[i][c1]);
//         }
//     }
//     c1 = 0;
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             cin >> b[i][j];
//             if(b[i][j] == 1) c1 = j;
//         }
//     }
//     if(c1 != 1) {
//         for(int i = 1; i <= n; i++) {
//             swap(b[i][1], b[i][c1]);
//         }
//     }
//     sort(a.begin() + 1, a.end(), [&](auto a, auto b){
//         return a[1] < b[1];
//     });
//     sort(b.begin() + 1, b.end(), [&](auto a, auto b){
//         return a[1] < b[1];
//     });
//     vector<int> p(m + 1), q(m + 1);
//     iota(p.begin(), p.end(), 0);
//     iota(q.begin(), q.end(), 0);
//     sort(p.begin() + 1, p.end(), [&](auto x, auto y){
//         return a[1][x] < a[1][y];
//     });
//     sort(q.begin() + 1, q.end(), [&](auto x, auto y){
//         return b[1][x] < b[1][y];
//     });
//     for(int i = 1; i <= n; i++) {
//         for(int j = 1; j <= m; j++) {
//             if(a[i][p[j]] != b[i][q[j]]) {
//                 cout << "NO\n";
//                 return;
//             }
//         }
//     }
//     cout << "YES\n";
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
