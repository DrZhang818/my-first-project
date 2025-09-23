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
    s += "#";
 
    vector<array<int,2>> dp(n + 1);
    dp[0][0] = dp[0][1] = 1;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '1') {
            if(s[i - 1] == '1' || s[i - 1] == '#') {
                dp[i] = dp[i - 1];
            } else {
                if(dp[i - 1][0]) {
                    dp[i][0] = dp[i][1] = 1;
                } 
            }
        } else {
            if(s[i - 1] == '0') {
                dp[i][0] |= dp[i - 1][0] | dp[i - 1][1];
                dp[i][1] |= dp[i - 1][0] | dp[i - 1][1];
            } else if(s[i - 1] == '1') {
                dp[i][1] |= dp[i - 1][0];
                if(i - 2 >= 0) {
                    if(s[i - 2] == '#' || s[i - 2] == '1') {
                        dp[i][0] = 0;
                    } else {
                        dp[i][0] = dp[i - 2][1];
                    }
                }
            } else {
                dp[i][0] = dp[i][1] = 1;
            }
        }
    }
    if(dp[n][0] || dp[n][1]) {
        cout << "YES\n";
    } else {
       cout << "NO\n";
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
