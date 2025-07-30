#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minSideJumps(vector<int>& a) {
        int n = a.size();
        vector<array<int,3>> dp(n + 1, {inf,inf,inf});
        dp[0][1] = 0;
        for(int i = 0; i < n - 1; i++) {
            auto t = dp[i];
            if(a[i] != 1) dp[i][0] = min({t[0], t[1] + 1, t[2] + 1});
            if(a[i] != 2) dp[i][1] = min({t[1], t[0] + 1, t[2] + 1});
            if(a[i] != 3) dp[i][2] = min({t[2], t[0] + 1, t[1] + 1});
            if(a[i + 1] != 1) dp[i + 1][0] = dp[i][0];
            if(a[i + 1] != 2) dp[i + 1][1] = dp[i][1];
            if(a[i + 1] != 3) dp[i + 1][2] = dp[i][2];
        }
        return min({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
    }
};