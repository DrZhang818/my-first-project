#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://ac.nowcoder.com/acm/contest/24213/1023
struct info {
    int w, b, c;
    friend bool operator < (const info &x, const info &y) {
        return x.b * y.c > y.b * x.c;
    }
};
void solve() {
    int n, m, t;
    cin >> n >> m >> t;
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<info> a(m + 1); 
    for(int i = 1; i <= m; i++) {
        cin >> a[i].b >> a[i].w >> a[i].c;
        a[i].b = b[a[i].b];
    }
    sort(a.begin() + 1, a.end());
    vector<ll> dp(t + 1, -inf);
    dp[0] = 0;
    ll ans = -inf;
    for(int i = 1; i <= m; i++) {
        for(int j = t; j >= a[i].c; j--) {
            dp[j] = max(dp[j], dp[j - a[i].c] + a[i].w - 1LL * j * a[i].b);
            ans = max(ans, dp[j]);
        }
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
