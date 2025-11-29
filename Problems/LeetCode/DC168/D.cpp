#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = int(1E9) + 7;
const int N = 150;

vector<int> fac[N + 1];
auto init = []() -> int {
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }

    return 1;
}();

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

class Solution {
public:
    int countCoprime(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        vector cnt(n, vector<int>(N + 1));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int x = a[i][j];
                for(int f : fac[x]) {
                    cnt[i][f]++;
                }
            }
        }
        vector<int> dp(N + 1);
        for(int g = 1; g <= N; g++) {
            int res = 1;
            for(int i = 0; i < n; i++) {
                res = 1LL * res * cnt[i][g] % MOD;
            }
            dp[g] = res;
        }
        for(int x = N; x >= 1; x--) {
            for(int y = x * 2; y <= N; y += x) {
                add(dp[x], MOD - dp[y]);
            }
        }
        return dp[1];
    }
};