#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = ll(1E18);

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());

    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, inf));
    for(int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int x = 0; x <= m; x++) {
            dp[i][x] = 1LL * (a[i] + x) * i - pre[i];
        }
        for(int j = 1; j < i; j++) {
            for(int x = m; x >= 0; x--) {
                int y = min(m, a[i] + x - a[j] - m);
                if(y < 0) {
                    break;
                }
                dp[i][x] = min(dp[i][x], dp[j][y] + 1LL * (a[i] + x) * (i - j) - pre[i] + pre[j]);
            }
        }

        for(int x = 1; x <= m; x++) {
            dp[i][x] = min(dp[i][x], dp[i][x - 1]);
        }

    }

    cout << *min_element(dp[n].begin(), dp[n].end()) << "\n";
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
