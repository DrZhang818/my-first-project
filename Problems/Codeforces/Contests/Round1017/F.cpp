#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj(n, vector<int>(m));

    int x = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            adj[i][j] = x;
            x = x % k + 1;
        }
        if(m % k == 0) {
            x = x % k + 1;
        }
    }

    for(int i = 0; i < n; i++) {
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
