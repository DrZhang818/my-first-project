#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void chmax(int &x, int y) {
    if(x < y) {
        x = y;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector dp(1 << m + 1, -inf);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            vector ndp(1 << m + 1, -inf);
            for(int s = 0; s < 1 << m + 1; s++) {
                if(dp[s] == -inf) {
                    continue;
                }
                int ns = s & ~(1 << j);
                if(j == 0) {
                    ns = (s << 1) & ~(1 << m + 1);
                }
                chmax(ndp[ns], dp[s]);
                ns |= 1 << j;
                if(j == 0) {
                    if((~s >> 1 & 1) || (~s & 1)) {
                        chmax(ndp[ns], dp[s] + a[i][j]);
                    }
                } else if((~s >> j - 1 & 1) && (~s >> j + 1 & 1)) {
                    chmax(ndp[ns], dp[s] + a[i][j]);
                } else if((~s >> j - 1 & 1) && (~s >> j & 1) && (~s >> j + 2 & 1)) {
                    chmax(ndp[ns], dp[s] + a[i][j]);
                } else if((~s >> j + 1 & 1) && (~s >> j & 1)) {
                    chmax(ndp[ns], dp[s] + a[i][j]);
                }
            }
            swap(dp, ndp);
        }
    }
    int ans = ranges::max(dp);
    cout << ans << "\n";
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
