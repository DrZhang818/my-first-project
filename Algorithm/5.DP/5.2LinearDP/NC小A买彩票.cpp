#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/24213/1014
PLL add(PLL p, PLL q) {
    auto [a, b] = p;
    auto [c, d] = q;
    ll g = gcd(b, d);
    ll u = d / g * a + b / g * c;
    ll v = b / g * d;
    g = gcd(u, v);
    return {u / g, v / g};
}
PLL div(PLL o, int x) {
    auto [a, b] = o;
    b *= 4;
    ll g = gcd(a, b);
    return {a / g, b / g};
}
void solve() {
    int n;
    cin >> n;
    vector<PLL> dp(4 * n + 1, {0, 1});
    dp[3 * n] = {1, 1};
    for(int i = 0; i < n; i++) {
        vector<PLL> ndp(4 * n + 1, {0, 1});
        for(int j = 3 * n - 2 * i; j <= 3 * n + i; j++) {
            for(int k = -2; k <= 1; k++) {
                ndp[j + k] = add(ndp[j + k], div(dp[j], 4));
            }
        }
        swap(dp, ndp);
    }
    PLL ans = {0, 1};
    for(int j = 3 * n; j <= 4 * n; j++) {
        ans = add(ans, dp[j]);
    }
    cout << ans.first << "/" << ans.second << "\n";
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
