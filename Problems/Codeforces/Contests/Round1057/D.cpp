#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

int get(int x, int y, int z) {
    return max({x, y, z}) - min({x, y, z});
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a.push_back(a[1]);
    a.push_back(a[2]);
    auto work = [&](int l, int r) {
        vector<ll> dp(n + 1, inf);
        dp[0] = 0;
        for(int i = 2; i <= n; i++) {
            dp[i] = dp[i - 2] + abs(a[i + l - 1] - a[i + l - 2]);
            if(i >= 3) {
                int x = a[i + l - 1], y = a[i + l - 2], z = a[i + l - 3];
                dp[i] = min(dp[i], dp[i - 3] + get(x, y, z));
            }
        }
        return dp[n];
    };
    ll ans = min({work(1, n), work(2, n + 1), work(3, n + 2)});
    cout << ans << "\n";
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
