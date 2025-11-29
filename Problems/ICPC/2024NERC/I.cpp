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
    vector<vector<int>> a(n + 1, vector<int>(2 * m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            a[i][j] = a[i][m + j] = c - '0';
        }
    }

    vector<int> las(n + 1, -1);
    vector<int> nxt(2 * m + 1);
    for(int j = 2 * m - 1; j >= 1; j--) {
        int mn = inf;
        for(int i = 1; i <= n; i++) {
            if(a[i][j] == 1) {
                mn = min(mn, las[i]);
                las[i] = j;
            }
        }
        if(mn - j < m) {
            nxt[j] = mn;
        }
    }
    for(int j = 1; j <= 2 * m - 1; j++) {
        cerr << nxt[j] << " \n"[j == 2 * m - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
