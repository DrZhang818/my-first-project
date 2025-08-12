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
    vector<array<int,4>> dp(2, {inf,inf,inf,inf});
    if(s[1] == '0') {
        dp[0][0] = 0;
        dp[1][0] = 1;
    } else {
        dp[0][0] = 1;
        dp[1][0] = 0;
    }
    for(int i = 2; i <= n; i++) {
        auto ndp = dp;
        char c = s[i];
        for(int s = 1; s <= 3; s++) {
            if(c == '0') {
                ndp[0][s] = min(ndp[0][s], dp[1][s - 1]);
                ndp[1][s] = min(ndp[1][s], dp[0][s - 1] + 1);
            } else {
                ndp[1][s] = min(ndp[1][s], dp[0][s - 1]);
                ndp[0][s] = min(ndp[0][s], dp[1][s - 1] + 1);
            }
        }
        swap(dp, ndp);
    }
    cout << min(dp[0][3], dp[1][3]) << "\n";
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
