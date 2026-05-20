#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

i64 C[5][5];

int init = []() {
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j <= i; j++) {
            if(j == 0) C[i][j] = 1;
            else C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    return 1;
}();

void solve() {
    int n, D;
    cin >> n >> D;
    vector<string> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<i64> dp(5);
    dp[0] = 1LL * n * (n - 1) / 2;

    for(int s = 1; s < 1 << 4; s++) {
        unordered_map<string, int> mp;
        int pc = __builtin_popcount(s);
        for(int i = 0; i < n; i++) {
            string cur;
            for(int j = 0; j < 4; j++) {
                if(s >> j & 1) {
                    cur += a[i][j];
                }
            }
            dp[pc] += mp[cur];
            mp[cur]++;
        }
    }

    i64 ans = 0;
    for(int i = 4 - D, s = 1; i <= 4; i++, s ^= 1) {
        if(s) {
            ans += C[i][4 - D] * dp[i];
        } else {
            ans -= C[i][4 - D] * dp[i];
        }
    }

    cout << ans << "\n";
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
