#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1));
    auto dfs = [&](auto &&self, int l, int r, int x) -> void {
        if(l == r) {
            return;
        }
        int m = l + r >> 1;
        for(int i = l; i <= m; i++) {
            for(int j = m + 1; j <= r; j++) {
                adj[i][j] = adj[j][i] = x;
            }
        }
        self(self, l, m, x + 1);
        self(self, m + 1, r, x + 1);
    };
    dfs(dfs, 1, n, 1);
    for(int i = 1; i <= n; i++) {
        for(int j = i + 1; j <= n; j++) {
            cout << adj[i][j] << " \n"[j == n];
        }
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
