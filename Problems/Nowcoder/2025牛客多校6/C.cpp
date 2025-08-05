#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int C[4][4];
const int N = 500000;
int dp[N + 1][4];
void solve() {
    int n;
    cin >> n;
    cout << dp[n][3] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 0; i <= 3; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = ((ll)C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
    dp[0][0] = 1;
    for(int n = 1; n <= N; n++) {
        for(int p = 0; p <= 3; p++) {
            dp[n][p] = 1LL * (n - 1) * dp[n - 1][p] % MOD;
            for(int i = 0; i <= p; i++) {
                add(dp[n][p], 1LL * dp[n - 1][i] * C[p][i] % MOD);
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
