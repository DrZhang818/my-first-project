#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    ll rob(vector<int>& a, vector<int>& col) {
        int n = a.size();
        vector<array<ll,2>> dp(n + 1);
        
        dp[0][1] = a[0];
        for(int i = 1; i < n; i++) {
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + a[i];
            if(col[i] == col[i - 1]) {
                if(i >= 2) {
                    dp[i][1] = max(dp[i - 2][0], dp[i - 2][1]) + a[i];
                }
            } else {
                dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]) + a[i];
            }
        }

        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};