#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<array<int,2>> dp(n + 1);
    dp[0][1] = inf;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = 1 + (i == 1 ? 0 : min(dp[i - 2][0], dp[i - 2][1]));
        } else {
            dp[i][0] = inf;
            dp[i][1] = (i == 1 ? 0 : min(dp[i - 2][0], dp[i - 2][1]));
        }
    }
    cout << min(dp[n][0], dp[n][1]) + count(s.begin(), s.end(), '1') << "\n";
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
