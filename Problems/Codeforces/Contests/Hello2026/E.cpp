#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

vector<int> adj[3001];

void solve() {  
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(a[1] > 1) {
        cout << 0 << "\n";
        return;
    }
    vector<int> dp(m + 1);
    dp[1] = 1;
    for(int i = 2; i <= n; i++) {
        vector<int> ndp(m + 1);
        if(a[i] != 0) {
            for(int v : adj[a[i]]) {
                add(ndp[a[i]], dp[v]);
            }
        } else {
            for(int j = 1; j <= m; j++) {
                for(int v : adj[j]) {
                    add(ndp[j], dp[v]);
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for(int j = 1; j <= m; j++) {
        add(ans, dp[j]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int y = 2; y <= 3000; y++) {
        for(int x = 1; x < y; x++) {
            if((y - x) * lcm(x, y) == x * y) {
                adj[y].push_back(x);
            }
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
