#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 2015;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector dp(n + 1, vector<int>(n + 1));
    dp[1][0] = 1;
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            add(dp[i + 1][j + 1], (i - j) * dp[i][j] % MOD);
            add(dp[i + 1][j], (j + 1) * dp[i][j] % MOD);
        }
    }
    cout << dp[n][k] << "\n";
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
