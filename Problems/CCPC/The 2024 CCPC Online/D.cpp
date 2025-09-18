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

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    s = "#" + s;
    t = "#" + t;
    vector dp(m + 1, vector<int>(m + 1));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        for(int j = 1; j <= m; j++) {
            for(int k = j; k <= m; k++) {
                if(t[k] == s[i]) {
                    if(k == j) {
                        add(ndp[j][k], 1);
                    } else {
                        add(ndp[j][k], dp[j][k - 1]);
                    }
                }
            }
        }
        auto nndp = ndp;
        for(int j = 1; j < m; j++) {
            for(int k = j + 1; k <= m; k++) {
                for(int w = j; w < k; w++) {
                    add(nndp[j][k], 1LL * ndp[j][w] * dp[w + 1][k] % MOD);
                }
            }
        }
        for(int j = 1; j <= m; j++) {
            for(int k = j; k <= m; k++) {
                add(nndp[j][k], dp[j][k]);
            }
        }
        swap(dp, nndp);
    }
    cout << dp[1][m] << "\n";
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
