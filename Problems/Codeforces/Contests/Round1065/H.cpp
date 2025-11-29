#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int cal(int b, int x) {
    int c = 0;
    while(x % b == 0) {
        c++;
        x /= b;
    }
    return c;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector dp(n + 1, vector<int>(m + 1));
    for(int i = 2; i <= n; i++) {
        for(int j = i; j <= m; j++) {
            dp[i][j] = dp[i - 1][j - 1] + cal(i, j);
        }
        for(int j = i; j <= m; j++) {
            dp[i][j] = max(dp[i][j - 1], dp[i][j]);
        }
    }
    for(int j = n; j <= m; j++) {
        cerr << "(" << n << "," << j << ") : " << dp[n][j] << "\n";
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
