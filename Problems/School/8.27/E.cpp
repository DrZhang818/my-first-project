#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int u, v;
};
void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<vector<int>> dp(x + 1, vector<int>(n + 1, inf));
    dp[0][0] = 0;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].u >> a[i].v;
    }
    for(int i = 1; i <= n; i++) {
        auto ndp = dp;
        auto [u, v] = a[i];
        for(int k = 0; k < i; k++) {
            for(int j = 0; j + u <= x; j++) {
                if(dp[j][k] + v <= y) {
                    ndp[j + u][k + 1] = min(ndp[j + u][k + 1], dp[j][k] + v);
                }
            }
        }
        swap(dp, ndp);
    }
    for(int i = n; i >= 0; i--) {
        for(int j = 0; j <= x; j++) {
            if(dp[j][i] != inf) {
                if(i == n) {
                    cout << n << "\n";
                } else {
                    cout << i + 1 << "\n";
                }
                return;
            }
        }
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
