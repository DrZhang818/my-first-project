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
    if(m >= 2 * n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector adj(2 * n, vector<int>(2 * n));
    for(int i = 0; i < 2 * n; i += 2) {
        for(int j = 0, s = i; j < m; j++) {
            adj[(s + j) % (2 * n)][j] = i / 2 + 1;
            adj[(s + j + 1) % (2 * n)][j] = i / 2 + 1;
        }
    }
    for(int i = 0; i < 2 * n; i++) {
        for(int j = 0; j < m; j++) {
            cout << adj[i][j] << " \n"[j == m - 1];
        }
    }
}

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
