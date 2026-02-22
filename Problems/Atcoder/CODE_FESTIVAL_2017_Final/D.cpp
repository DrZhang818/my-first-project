#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr ll inf = 1E18;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](auto x, auto y) {
            return a[x] - b[y] < a[y] - b[x];
        });


    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, inf));
    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < i; j++) {
            if(dp[i - 1][j] <= a[p[i]]) {
                dp[i][j + 1] = min(dp[i][j + 1], dp[i - 1][j] + b[p[i]]);
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
        }
    }

    for(int i = n; i >= 1; i--) {
        if(dp[n][i] != inf) {
            cout << i << "\n";
            return;
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
