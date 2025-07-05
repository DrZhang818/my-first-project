#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    a[0].l = a[0].r = 1;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
    }
    vector<vector<int>> dp(n + 1, vector<int>(2, inf));
    dp[0][0] = dp[0][1] = 0;
    for(int i = 1; i <= n; i++) {
        int x = a[i].l, y = a[i].r;
        int px = a[i - 1].l, py = a[i - 1].r;
        if(px < y) {
            dp[i][0] = min(dp[i][0], dp[i - 1][0] + y - px + y - x);
        } else {
            dp[i][0] = min(dp[i][0], dp[i - 1][0] + px - x);
        }
        if(py < x) {
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + y - py);
        } else {
            dp[i][1] = min(dp[i][1], dp[i - 1][1] + py - x + y - x);
        }
        if(py < y) {
            dp[i][0] = min(dp[i][0], dp[i - 1][1] + y - py + y - x);
        } else {
            dp[i][0] = min(dp[i][0], dp[i - 1][1] + py - x);
        }
        if(px < x) {
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + y - px);
        } else {
            dp[i][1] = min(dp[i][1], dp[i - 1][0] + px - x + y - x);
        }
    }
    cout << n - 1 + min(dp[n][0] + n - a[n].l, dp[n][1] + n - a[n].r) << "\n";
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
