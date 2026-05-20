#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 5000;
constexpr int MOD = 998244353;

void add(int& x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].first;
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i].second;
    }
    sort(a.begin() + 1, a.end());

    vector<int> dp(N + 1);
    dp[0] = 1;

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        auto [A, B] = a[i];
        for(int j = N - a[i].second; j >= 0; j--) {
            add(dp[j + B], dp[j]);
            if(j + B <= A) {
                add(ans, dp[j]);
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
