#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc411/tasks/abc411_g
/*
    

*/
const int MOD = 998244353;
const int inv2 = (MOD + 1) >> 1;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> lg(1 << n);
    lg[0] = -1;
    for(int i = 1; i < 1 << n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    vector a(n, vector<int>(n));
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        a[u][v]++;
        a[v][u]++;
    }
    int ans = 0;
    vector dp(n, vector<int>(1 << n));
    for(int i = 0; i < n; i++) {
        dp[i][1 << i] = 1;
    }
    for(int s = 0; s < 1 << n; s++) {
        for(int i = 0; i < n; i++) {
            if(s >> i & 1) {
                for(int j = 0; j < lg[s]; j++) {
                    if(s >> j & 1) continue;
                    add(dp[j][s | 1 << j], 1LL * dp[i][s] * a[i][j] % MOD);
                }
            }
        }
    }
    for(int s = 0; s < 1 << n; s++) {
        int sz = __builtin_popcount(s);
        if(sz < 3) continue;
        for(int i = 0; i < lg[s]; i++) {
            if(s >> i & 1) {
                add(ans, 1LL * dp[i][s] * a[i][lg[s]] % MOD);
            }
        }
    }
    ans = 1LL * ans * inv2 % MOD;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            add(ans, 1LL * a[i][j] * (a[i][j] - 1) / 2 % MOD);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
