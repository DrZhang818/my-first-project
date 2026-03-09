#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    map<int,int> dp;
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(!dp.contains(x)) {
            dp[x] = 1;
        }
        if(dp.contains(x - 1)) {
            dp[x] = max(dp[x], dp[x - 1] + 1);
        }
        ans = max(ans, dp[x]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
