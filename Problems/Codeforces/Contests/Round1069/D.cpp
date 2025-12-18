#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int mx = 0;
    vector<int> tag(n + 1);
    for(int i = 1; i <= n; i++) {
        if(a[i] <= mx) continue;
        mx = a[i];
        tag[i] = 1;
    }
    vector<int> dp(k + 1);
    vector g(k + 1, vector<int>(k + 1));
    for(int i = 0; i <= k; i++) {
        for(int j = 0; j <= k; j++) {
            g[i][j] = (n + 1) * j;
        }
    }
    for(int i = n; i >= 1; i--) {
        if(!tag[i]) continue;
        auto ndp = dp;
        for(int s = 0; s <= k; s++) {
            for(int j = 0; j <= s && j <= a[i]; j++) {
                ndp[s] = max(ndp[s], g[s - j][j] - i * j);
            }
        }
        swap(dp, ndp);
        for(int s = 0; s <= k; s++) {
            for(int j = 0; j <= k; j++) {
                g[s][j] = max(g[s][j], dp[s] + i * j);
            }
        }
    }
    cout << dp[k] << "\n";
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
