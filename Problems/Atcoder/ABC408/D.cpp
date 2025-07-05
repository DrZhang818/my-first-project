#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<array<int,2>> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + (s[i] != '0');
        dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + (s[i] != '1');
    }
    vector<int> dp2(n + 1);
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') {
            dp2[i] = dp2[i - 1];
        } else {
            dp2[i] = min(dp2[i - 1] + 1, min(dp[i - 1][0], dp[i - 1][1]));
        }
    }
    cout << dp2[n] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
