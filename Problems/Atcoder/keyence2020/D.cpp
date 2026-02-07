#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int dp[1 << 18][18];

void chmin(int& x, int y) {
    if(x > y) {
        x = y;
    }
}

void solve() {      
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }

    for(int s = 0; s < 1 << n; s++) {
        for(int i = 0; i < n; i++) {
            dp[s][i] = inf;
        }
    }

    for(int i = 0; i < n; i++) {
        dp[1 << i][i] = 0;
    }

    for(int s = 1; s < 1 << n; s++) {
        int cnt = __builtin_popcount(s);
        for(int i = 0; i < n; i++) {
            if(~s >> i & 1) continue;
            int x = (cnt % 2 == i % 2) ? b[i] : a[i];

            int c = 0;
            for(int j = n - 1; j >= 0; j--) {
                if(s >> j & 1) {
                    c++;
                    continue;
                }
                int y = (cnt % 2 == j % 2) ? a[j] : b[j];
                if(x <= y) {
                    chmin(dp[s | 1 << j][j], dp[s][i] + c);
                }
            }
        }
    }

    int ans = inf;
    for(int i = 0; i < n; i++) {
        chmin(ans, dp[(1 << n) - 1][i]);
    }

    if(ans == inf) {
        cout << -1 << "\n";
        return;
    }
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
