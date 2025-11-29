#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    s = "#" + s;
    vector<vector<int>> adj(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector dp(n + 1, vector<array<char,2>>(2 * k + 1, {'?', '?'}));
    auto dfs = [&](auto &&self, int u, int rem, int op) -> char {
        if(rem == 0) {
            return s[u];
        }
        if(dp[u][rem][op] != '?') {
            return dp[u][rem][op];
        }
        char res = op == 0 ? 'B' : 'A';
        for(int v : adj[u]) {
            char c = self(self, v, rem - 1, op ^ 1);
            if(c != res) {
                res = c;
                break;
            }
        }
        return dp[u][rem][op] = res;
    };
    char res = dfs(dfs, 1, 2 * k, 0);
    if(res == 'A') {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
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
