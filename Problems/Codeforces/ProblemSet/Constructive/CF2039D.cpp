#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 100000;

int dp[N + 1];

auto init = []() {
    dp[1] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = i << 1; j <= N; j += i) {
            dp[j] = max(dp[j], dp[i] + 1);
        }
    }
    return 1;
}();

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    sort(a.begin() + 1, a.end(), greater());

    vector<int> ans(n + 1);
    for(int i = 1; i <= n; i++) {
        if(dp[i] > m) {
            cout << -1 << "\n";
            return;
        }
        ans[i] = a[dp[i]];
    }

    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }

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
