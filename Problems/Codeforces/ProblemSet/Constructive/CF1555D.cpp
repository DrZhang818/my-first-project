#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1555/D
/*
    前缀和
    题意:
        

*/
void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<vector<int>> dp(6, vector<int>(n + 1));
    vector<string> b = {"abc", "acb", "bac", "bca", "cab", "cba"};
    for(int i = 0; i < 6; i++) {
        for(int j = 1; j <= n; j++) {
            dp[i][j] = dp[i][j - 1];
            if(s[j - 1] != b[i][j % 3]) {
                dp[i][j] += 1;      
            }
        }
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        int ans = inf;
        for(int i = 0; i < 6; i++) {
            ans = min(ans, dp[i][r] - dp[i][l - 1]);
        }
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
