#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int f[35][65], g[35][65];
int pre[35][65];


void solve() {  
    int n, k;
    cin >> n >> k;
    int d = __lg(n);
    int ans = n;
    if(k < 2 * d) {
        ans -= pre[d][k];
    } else {
        ans = 1;
    }
    if(k >= d + 1) {
        ans -= 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    f[1][1] = 1, g[1][0] = 1;
    for(int i = 1; i <= 29; i++) {
        for(int j = 0; j < 2 * i; j++) {
            f[i + 1][j + 2] += f[i][j] + g[i][j];
            g[i + 1][j + 1] += f[i][j] + g[i][j];
        }
    }

    for(int i = 1; i <= 30; i++) {
        for(int j = 1; j < 2 * i; j++) {
            pre[i][j] += pre[i - 1][j] + f[i][j];
        }
    }

    for(int i = 1; i <= 30; i++) {
        for(int j = 1; j < 2 * i; j++) {
            pre[i][j] += pre[i][j - 1];
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
