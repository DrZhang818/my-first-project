#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int minXor(vector<int>& a, int k) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector<int> pre(n + 1);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] ^ a[i];
        }
        vector dp(n + 1, vector<int>(k + 1, INT_MAX));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < i; j++) {
                for(int s = 1; s <= k; s++) {
                    dp[i][s] = min(dp[i][s], max(dp[j][s - 1], pre[i] ^ pre[j]));         
                }
            }
        }
        return dp[n][k];
    }
};