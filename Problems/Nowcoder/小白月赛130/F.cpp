#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    i64 ans = 0;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 1) {
                cnt++;
                ans += i + j;
            }
        }
    }
    if(cnt % n) {
        cout << -1 << "\n";
        return;
    }

    vector<vector<int>> suf(n + 2, vector<int>(m + 2));
    for(int j = 1; j <= m; j++) {
        for(int i = n; i >= 1; i--) {
            suf[i][j] = a[i][j] + suf[i + 1][j];
        }
    }

    auto ck = [&](const vector<int>& x) {
        vector<int> dp(n + 1);
        for(int j = 1; j <= m; j++) {
            int mx = -inf;
            for(int i = 0; i <= n; i++) {
                mx = max(mx, dp[i]);
                dp[i] = mx + x[j] * i - suf[n - i + 1][j];
            }
        }
        int mx = -inf;
        for(int i = 0; i <= n; i++) {
            mx = max(mx, dp[i]);
        }
        return mx <= 0;
    };

    int rem = cnt / n;
    vector<int> x(m + 1);
    for(int i = 1; i <= rem; i++) {
        x[i] = 1;
    }
    if(!ck(x)) {
        cout << -1 << "\n";
        return;
    }

    for(int j = 1; j <= m; j++) {
        if(rem == 0) break;
        if(rem == m - j + 1) {
            x[j] = 1;
            rem--;
            continue;
        }

        auto tmp = x;
        tmp[j] = 0;
        for(int p = j + 1; p <= j + rem; p++) {
            tmp[p] = 1;
        }
        if(ck(tmp)) {
            x[j] = 0;
        } else {
            x[j] = 1;
            rem--;
        }
    }

    for(int j = 1; j <= m; j++) {
        if(x[j] == 1) {
            for(int i = 1; i <= n; i++) {
                ans -= i + j;
            }
        }
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
