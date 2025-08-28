#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<ll> dp(101);
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= 100; i++) {
        for(int j = i % 2 == 0 ? 1 : 0; j < i; j += 2) {
            dp[i] += dp[j];
        }
    }
    for(int i = 1; i <= 100; i++) {
        cout << dp[i] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
