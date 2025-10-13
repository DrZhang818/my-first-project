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

class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        vector<array<int,2>> dp(r + 1);
        for(int i = l; i <= r; i++) {
            dp[i][0] = dp[i][1] = 1;
        }
        for(int i = 2; i <= n; i++) {
            vector<array<int,2>> ndp(r + 1);
            vector<int> f(r + 1), g(r + 1);
            for(int j = l; j <= r; j++) {
                add(f[j], f[j - 1] + dp[j][0]);
                add(g[j], g[j - 1] + dp[j][1]);
            }
            for(int j = l; j <= r; j++) {
                add(ndp[j][0], (g[r] - g[j] + MOD) % MOD);
                add(ndp[j][1], f[j - 1]);
            }
            swap(dp, ndp);
        }
        int ans = 0;
        for(int i = l; i <= r; i++) {
            add(ans, dp[i][0]);
            add(ans, dp[i][1]);
        }
        return ans;
    }
};
