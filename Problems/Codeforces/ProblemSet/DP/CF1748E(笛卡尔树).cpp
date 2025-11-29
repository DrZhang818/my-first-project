#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> ls(n + 1), rs(n + 1);
    vector<int> stk(n + 1);
    int top = 0;
    for(int i = 1; i <= n; i++) {
        int k = 0;
        while(top && a[i] > a[stk[top]]) {
            k = stk[top--];
        }
        if(top) {
            rs[stk[top]] = i;
        }
        if(k) {
            ls[i] = k;
        }
        stk[++top] = i;
    }
    int rt = stk[1];
    vector dp(n + 1, vector<int>(m + 1, 1));
    auto dfs = [&](this auto &&self, int u) -> void {
        dp[u][0] = 0;
        if(ls[u]) {
            self(ls[u]);
            for(int i = 1; i <= m; i++) {
                dp[u][i] = 1LL * dp[u][i] * dp[ls[u]][i - 1] % MOD;
            }
        }
        if(rs[u]) {
            self(rs[u]);
            for(int i = 1; i <= m; i++) {
                dp[u][i] = 1LL * dp[u][i] * dp[rs[u]][i] % MOD;
            }
        }
        for(int i = 1; i <= m; i++) {
            add(dp[u][i], dp[u][i - 1]);
        }
    };
    dfs(rt);
    cout << dp[rt][m] << "\n";
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
