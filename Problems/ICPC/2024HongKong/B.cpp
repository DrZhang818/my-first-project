#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int k;
    cin >> k;
    vector<int> c(k + 1);
    for(int i = 1; i <= k; i++) {
        cin >> c[i];
    }
    int mx = 0;
    for(int i = 1; i <= n; i++) {
        mx = max(mx, a[i] + b[i]);
    }
    
    vector<int> need(mx + 2 * k);
    for(int i = 1; i <= n; i++) {
        need[b[i]] = max(need[b[i]], a[i]);
    }
    for(int i = mx + 2 * k - 2; i >= 1; i--) {
        need[i] = max(need[i], need[i + 1]);
    }

    ll ans = inf;
    int cnt = 0;
    for(int s = mx; s <= mx + 2 * k - 2; s++) {
        vector<ll> f(s + 1, inf);
        vector<int> g(s + 1, 0);
        f[0] = 0, g[0] = 1;
        for(int i = 0; i < s; i++) {
            for(int j = 1; j <= k && s - (i + j) >= need[i + 1]; j++) {
                if(f[i] + c[j] < f[i + j]) {
                    f[i + j] = f[i] + c[j];
                    g[i + j] = g[i];
                } else if(f[i] + c[j] == f[i + j]) {
                    add(g[i + j], g[i]);
                }
            }
        }
        if(f[s] < ans) {
            ans = f[s];
            cnt = g[s];
        } else if(f[s] == ans) {
            add(cnt, g[s]);
        }
    }
    cout << ans << " " << cnt << "\n";
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
