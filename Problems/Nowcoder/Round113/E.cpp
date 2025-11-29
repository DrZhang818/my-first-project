#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    std::vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<array<int,495>> f(n + 1), g(n + 1);
    f[0][0] = g[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int k = i - 1; k >= 0; k--) {
            for(int j = 0; j < 495; j++) {
                add(f[k + 1][(j + a[i]) % 495], f[k][j]);
                add(g[k + 1][(j + b[i]) % 495], g[k][j]);
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 495; j++) {
            add(g[i][j], g[i - 1][j]);
        }
    }
    vector<int> ans(495);
    for(int s = 0; s < 495; s++) {
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j < 495; j++) {
                add(ans[s], 1LL * f[i][j] * g[i][(s - j + 495) % 495] % MOD);
            }
        }
        cout << ans[s] << " \n"[s == 494];
    }

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
