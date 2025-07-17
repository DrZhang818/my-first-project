#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<ll,ll> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

PII add(PII x, PII y) {
    auto [a, b] = x;
    auto [c, d] = y;
    ll p, q;
    ll g = __gcd(b, d);
    p = d / g * a + b / g * c;
    q = b / g * d * 2;
    g = __gcd(p, q);
    p /= g;
    q /= g;
    return {p, q};
}
void solve() {
    int n, m;
    cin >> n >> m;
    m++;
    vector a(n + 2, vector<int>(n + 2));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            char c;
            cin >> c;
            a[i][j] = c == '*';
        }
    }
    vector dp(n + 2, vector(n + 2, vector<PII>(n + 2, {0, 1})));
    for(int i = 1; i <= n + 1; i++) {
        dp[n + 1][i][i] = {1, 1};
    }
    for(int i = n; i >= 1; i--) {
        for(int j = 1; j <= i; j++) {
            if(a[i][j] == 1) {
                for(int k = 1; k <= n + 1; k++) {
                    dp[i][j][k] = add(dp[i + 1][j][k], dp[i + 1][j + 1][k]);
                }
            } else {
                for(int k = 1; k <= n + 1; k++) {
                    dp[i][j][k] = dp[i + 2][j + 1][k];
                }
            }
        }
    }
    auto [p, q] = dp[1][1][m];
    cout << p << "/" << q << "\n";
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
