#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    s = "#" + s;

    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));

    vector<int> pre0(n + 1), pre1(n + 1), suf0(n + 2, n + 1), suf1(n + 2, n + 1);
    
    for(int i = 1; i <= n; i++) {
        if(s[i] == '(') {
            pre0[i] = i;
            pre1[i] = pre1[i - 1];
        } else {
            pre0[i] = pre0[i - 1];
            pre1[i] = i;
        }
    }

    for(int i = n; i >= 1; i--) {
        if(s[i] == '(') {
            suf0[i] = i;
            suf1[i] = suf1[i + 1];
        } else {
            suf0[i] = suf0[i + 1];
            suf1[i] = i;
        }
    }

    for(int L = 1; L < n; L++) {
        for(int R = n; R > L; R--) {
            if(pre0[L] == 0 || suf1[R] == n + 1) continue;
            dp[L][R] = 0;

            int x = pre0[L];
            if(x > 0) x = pre1[x];
            int y = suf0[R];
            if(y <= n) y = suf1[y];

            if(x >= 1 && y <= n && dp[x - 1][y + 1] != -1) {
                dp[L][R] = max(dp[L][R], dp[x - 1][y + 1] + 4);
            }

            x = pre1[L];
            if(x > 0) x = pre0[x];
            y = suf1[R];
            if(y <= n) y = suf0[y];

            if(x >= 1 && y <= n && dp[x - 1][y + 1] != -1) {
                dp[L][R] = max(dp[L][R], dp[x - 1][y + 1] + 4);                
            }

            dp[L][R] = max(dp[L][R], dp[L][R + 1]);
            dp[L][R] = max(dp[L][R], dp[L - 1][R]);            
        }
    }

    int ans = 0;
    for(int i = 1; i < n; i++) {
        if(dp[i][i + 1] != -1) {
            ans = max(ans, dp[i][i + 1] + 2);
        }
    }

    cout << ans << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}