#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
//https://ac.nowcoder.com/acm/contest/24213/1002
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    vector<array<int,3>> dp(3);
    int n;
    cin >> n;
    dp[0][1] = dp[1][1] = dp[2][1] = 1;
    for(int i = 2; i <= n; i++) {
        vector<array<int,3>> ndp(3);
        for(int j = 0; j < 3; j++) {
            for(int k = 1; k < 3; k++) {
                add(ndp[j][1], dp[(j + 1) % 3][k]);
                add(ndp[j][1], dp[(j + 2) % 3][k]);
                if(k) add(ndp[j][k], dp[j][k - 1]);
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for(int j = 0; j < 3; j++) {
        for(int k = 0; k < 3; k++) {
            add(ans, dp[j][k]);
        }
    }
    cout << ans << "\n";
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
