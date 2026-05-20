#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m, k, d;
    cin >> n >> m >> k >> d;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    vector<i64> w(n + 1);

    for(int i = 1; i <= n; i++) {
        vector<i64> dp(m + 1);
        dp[1] = 1;

        deque<int> q;
        q.push_back(1);

        for(int j = 2; j <= m; j++) {
            while(j - q.front() - 1 > d) {
                q.pop_front();
            }
            dp[j] = dp[q.front()] + a[i][j] + 1;
            while(!q.empty() && dp[j] <= dp[q.back()]) {
                q.pop_back();
            }
            q.push_back(j);
        }

        w[i] = dp[m];
    }

    i64 ans = numeric_limits<i64>::max(), cur = 0;
    for(int i = 1; i <= n; i++) {
        cur += w[i];
        if(i < k) continue;
        ans = min(ans, cur);
        cur -= w[i - k + 1];
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
