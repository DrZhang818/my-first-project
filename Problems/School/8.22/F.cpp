#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        ans++;
        x -= a[i];
    }
    vector<int> dp(x + 1, -inf);
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = a[i]; j <= x; j++) {
            dp[j] = max(dp[j], dp[j - a[i]] + 1);
        }
    }
    ans += *max_element(dp.begin(), dp.end());
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
