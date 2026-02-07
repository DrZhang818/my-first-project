#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;

void solve() {  
    int n;
    cin >> n;
    vector<array<int,5>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 5; j++) {
            cin >> a[i][j];
        }
    }

    auto ck = [&](int x) -> bool {
        vector<array<int, 1 << 5>> dp(4);
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            int cur = 0;
            for(int j = 0; j < 5; j++) {
                if(a[i][j] >= x) {
                    cur |= 1 << j;
                }
            }
            for(int j = 0; j < 3; j++) {
                for(int s = 0; s < 1 << 5; s++) {
                    dp[j + 1][s | cur] |= dp[j][s];
                }
            }
        } 
        return dp[3][(1 << 5) - 1];
    };

    int lo = 0, hi = inf;
    while(lo + 1 < hi) {
        int m = lo + hi >> 1;
        if(ck(m)) {
            lo = m;
        } else {
            hi = m;
        }
    }

    cout << lo << "\n";
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
