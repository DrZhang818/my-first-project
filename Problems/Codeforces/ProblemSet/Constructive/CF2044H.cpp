#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector a(n + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    vector f(n + 1, vector<ll>(n + 1)), g(n + 1, vector<ll>(n + 1)), h(n + 1, vector<ll>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            f[i][j] += a[i][j] + f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1];
            g[i][j] += 1LL * a[i][j] * j + g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1]; 
            h[i][j] += 1LL * a[i][j] * i + h[i - 1][j] + h[i][j - 1] - h[i - 1][j - 1];
        }
    }
    auto get = [&](int x1, int y1, int x2, int y2) -> ll {
        ll sum = f[x2][y2] - f[x1 - 1][y2] - f[x2][y1 - 1] + f[x1 - 1][y1 - 1]; 
        ll ans = 0;
        ans += g[x2][y2] - g[x1 - 1][y2] - g[x2][y1 - 1] + g[x1 - 1][y1 - 1];
        ans -= sum * (y1 - 1);
        ll add = h[x2][y2] - h[x1 - 1][y2] - h[x2][y1 - 1] + h[x1 - 1][y1 - 1];
        add -= sum * x1;
        ans += add * (y2 - y1 + 1);
        return ans;
    };
    for(int i = 1; i <= q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << get(x1, y1, x2, y2) << " \n"[i == q];
    }

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
