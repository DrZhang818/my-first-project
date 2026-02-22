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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<array<int,7>> dp(n + 1);
    for(int i = 1; i <= 6; i++) {
        if(a[1] != i) {
            dp[1][i] = 1;
        }
    }
    for(int i = 2; i <= n; i++) {
        for(int x = 1; x <= 6; x++) {
            dp[i][x] = inf;
            for(int y = 1; y <= 6; y++) {
                if(y == 7 - x || y == x) continue;
                dp[i][x] = min(dp[i][x], dp[i - 1][y] + (a[i] == x ? 0 : 1));
            }
        }
    }

    int mn = inf;
    for(int i = 1; i <= 6; i++) {
        mn = min(mn, dp[n][i]);
    }
    cout << mn << "\n";
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
