#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void chmin(int &x, int y) {
    if(x > y) x = y;
}

void solve() {  
    int n;
    cin >> n;
    vector<array<int,2>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1];
    }
    const int N = n * 5;

    vector<int> dp(2 * N + 1, inf);
    dp[N] = 0;
    for(int i = 0; i < n; i++) {
        vector<int> ndp(2 * N + 1, inf);
        int x = a[i + 1][0] - a[i + 1][1];
        for(int j = 0; j <= 2 * N; j++) {
            if(dp[j] == inf) continue;
            chmin(ndp[j + x], dp[j]);
            chmin(ndp[j - x], dp[j] + 1);
        }
        dp = move(ndp);
    }
    vector<int> mn(N + 1, inf);
    for(int i = 0; i <= 2 * N; i++) {
        chmin(mn[abs(i - N)], dp[i]);
    }
    for(int i = 0; i <= N; i++) {
        if(mn[i] != inf) {
            cout << mn[i] << "\n";
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
