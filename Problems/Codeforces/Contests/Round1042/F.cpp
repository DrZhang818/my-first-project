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
    string s, t;
    cin >> s >> t;
    s = "#" + s;
    t = "#" + t;
    vector<array<int,2>> f(n + 1), g(n + 1);
    for(int i = 1; i <= n; i++) {
        f[i][0] = f[i - 1][0] + (s[i] == '0');
        f[i][1] = f[i - 1][1] + (s[i] == '1');
        g[i][0] = g[i - 1][0] + (t[i] == '0');
        g[i][1] = g[i - 1][1] + (t[i] == '1');
    }
    sort(f.begin() + 1, f.end(), 
        [&](auto a, auto b) {
            return a[0] - a[1] > b[0] - b[1];
        });
    sort(g.begin() + 1, g.end(),
        [&](auto a, auto b) {
            return a[0] - a[1] > b[0] - b[1];
        });
    vector<ll> pre(n + 1), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + g[i][1];
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + g[i][0];
    }
    ll ans = 0;
    for(int i = 1, j = n; i <= n; i++) {
        while(j > 0 && f[i][0] + g[j][0] < f[i][1] + g[j][1]) {
            j--;
        }
        ans += pre[j] + suf[j + 1];
        ans += 1LL * f[i][1] * j;
        ans += 1LL * f[i][0] * (n - j);
    }
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
