#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/2052/F
void solve() {
    int n;
    cin >> n;
    vector a(3, vector<char>(n + 1));
    for(int i = 1; i <= 2; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    vector dp(n + 1, vector(2, vector<int>(2)));
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        char x = a[1][i], y = a[2][i];
        if(x == y) {
            dp[i][0][0] += dp[i - 1][0][0];
        } 
        if(x == '.' && y == '.') {
            dp[i][0][0] += dp[i - 1][1][1];
            dp[i][1][1] += dp[i - 1][0][0];
            dp[i][0][1] += dp[i - 1][1][0];
            dp[i][1][0] += dp[i - 1][0][1];
        }
        if(x == '.' && y == '#') {
            dp[i][0][0] += dp[i - 1][1][0];
            dp[i][1][0] += dp[i - 1][0][0];
        }
        if(x == '#' && y == '.') {
            dp[i][0][0] += dp[i - 1][0][1];
            dp[i][0][1] += dp[i - 1][0][0];
        }
        dp[i][0][0] = min(dp[i][0][0], 2);
        dp[i][0][1] = min(dp[i][0][1], 2);
        dp[i][1][0] = min(dp[i][1][0], 2);
        dp[i][1][1] = min(dp[i][1][1], 2);
    }
    int tag = dp[n][0][0];
    if(tag == 1) {
        cout << "Unique\n";
    } else if(tag > 1) {
        cout << "Multiple\n";
    } else {
        cout << "None\n";
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
