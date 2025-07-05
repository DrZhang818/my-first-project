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
    vector<array<ll,2>> dp(30);
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int s = 0; s < 30; s++) {
            int x = (a[i] >> s & 1);
            dp[s][0] += 1;
            ans += dp[s][x ^ 1] * (1 << s);
            if(x == 1) swap(dp[s][0], dp[s][1]);
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
