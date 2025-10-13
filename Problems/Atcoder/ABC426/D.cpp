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
    array<array<int,2>,2> dp;
    int pre0 = 0, pre1 = 0;
    if(s[0] == '0') {
        dp[0][0] = dp[0][1] = 0;
        dp[1][0] = dp[1][1] = 1;
        pre0 = 2, pre1 = 1;
    } else {
        dp[0][0] = dp[0][1] = 1;
        dp[1][0] = dp[1][1] = 0;
        pre0 = 1, pre1 = 2;
    }

    for(int i = 1; i < n; i++) {
        array<array<int,2>,2> ndp;
        if(s[i] == '0') {
            pre0 += 2;
            pre1 += 1;
            ndp[1][0] = pre1;
            ndp[1][1] = min(dp[1][0], dp[1][1]) + 1;
            ndp[0][0] = dp[0][0];
            ndp[0][1] = min(dp[0][0], dp[0][1] + 2);
        } else {
            pre0 += 1;
            pre1 += 2;
            ndp[0][0] = pre0;
            ndp[0][1] = min(dp[0][0], dp[0][1]) + 1;
            ndp[1][0] = dp[1][0];
            ndp[1][1] = min(dp[1][0], dp[1][1] + 2);
        }
        swap(dp, ndp);
    }
    cout << min({dp[0][0], dp[0][1], dp[1][0], dp[1][1]}) << "\n";
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
