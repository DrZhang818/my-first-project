#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    string s;
    cin >> s;
    int n = s.size();
    s = "#" + s;
    vector<vector<int>> dp(n + 2, vector<int>(n + 2));
    for(int i = n; i >= 1; i--) {
        for(int j = n; j >= 1; j--) {
            if(s[i] != s[j]) {
                dp[i][j] = dp[i + 1][j + 1] + 1;
            }
        }
    }
    ll ans = 0;
    for(int a = 1; a <= n; a++) {
        for(int c = a + 1; c <= n; c++) {
            ans += min({dp[a][c], c - a, n - c + 1});
        }
    }
    cout << ans << "\n";
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
