#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int inv2 = (MOD + 1) >> 1;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n;
    cin >> n;
    vector<array<int,2>> dp(5005);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        dp[x][0]++;
    }
    for(int i = 1; i <= 5000; i++) {
        for(int j = 1; j <= i && j + i <= 5000; j++) {
            if(j != i) add(dp[i + j][1], 1LL * dp[i][0] * dp[j][0] % MOD);
            else add(dp[i + j][1], 1LL * dp[i][0] * (dp[i][0] - 1) % MOD * inv2 % MOD);
        }
    }
    int ans = 0;
    for(int i = 1; i <= 5000; i++) {
        if(dp[i][0] >= 2 && dp[i][1] >= 1) {
            add(ans, 1LL * dp[i][1] * dp[i][0] % MOD * (dp[i][0] - 1) % MOD * inv2 % MOD);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
