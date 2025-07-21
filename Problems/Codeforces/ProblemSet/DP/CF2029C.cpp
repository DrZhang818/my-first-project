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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto cal = [&](int x, int y) {
        if(x > y) return 1;
        else if(x == y) return 0;
        else return -1;
    };
    vector<int> dp(3, -inf);
    dp[2] = 0;
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        vector<int> ndp(3);
        ndp[2] = dp[2] + cal(x, dp[2]);
        ndp[1] = max(dp[1], dp[2]);
        ndp[0] = max(dp[0] + cal(x, dp[0]), dp[1] + cal(x, dp[1]));
        swap(dp, ndp);
    }
    cout << max(dp[0], dp[1]) << "\n";
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
