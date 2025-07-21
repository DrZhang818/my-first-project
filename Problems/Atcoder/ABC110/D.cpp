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

//优化解法
int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> fac(n + 50), inv_fac(n + 50);
    fac[0] = inv_fac[0] = 1;
    for(int i = 1; i <= n + 49; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
        inv_fac[i] = fast_pow(fac[i], MOD - 2);
    }
    vector<int> a;
    for(int i = 2; i * i <= m; i++) {
        int c = 0;
        while(m % i == 0) {
            c++;
            m /= i;
        }
        if(c) a.push_back(c);
    }
    if(m != 1) a.push_back(1);
    int ans = 1;
    for(int c : a) {
        ans = 1LL * ans * fac[n + c - 1] % MOD * inv_fac[n - 1] % MOD * inv_fac[c] % MOD;
    }
    cout << ans << "\n";
}

// void solve() {
//     int n, m;
//     cin >> n >> m;
//     if(m == 1) {
//         cout << 1 << "\n";
//         return;
//     }
//     vector<int> fac;
//     for(int i = 1; i * i <= m; i++) {
//         if(m % i == 0) {    
//             if(i != 1) fac.push_back(i);
//             if(i * i != m) fac.push_back(m / i);
//         }
//     }
//     vector pre(n + 1, vector<int>(35));
//     for(int i = 0; i <= 34; i++) pre[0][i] = 1;
//     vector<int> sum(n + 1);
//     for(int j = 1; j <= 34; j++) {
//         sum[0] = 1;
//         for(int i = 1; i <= n; i++) {
//             sum[i] = (sum[i - 1] + pre[i][j - 1]) % MOD;
//         }
//         for(int i = 1; i <= n; i++) {
//             pre[i][j] = sum[i];
//         }
//     }
//     vector<map<int,int>> dp(35);
//     dp[0][1] = 1;
//     for(int i = 0; i < 34; i++) {
//         for(auto [x, c] : dp[i]) {
//             if(x == m) continue;
//             for(int p : fac) {
//                 if(1LL * x * p <= m && m % (x * p) == 0) add(dp[i + 1][x * p], c);
//             }
//         }
//     }
//     int ans = 0;
//     for(int i = 1; i <= min(n, 33); i++) {
//         int c = dp[i][m];
//         add(ans, 1LL * c * pre[n - i][i + 1] % MOD);
//     }
//     cout << ans << "\n";
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
