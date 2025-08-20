#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e15;
const int MOD = 1000000007;

class Solution {
public:
    ll minArraySum(vector<int>& a, int k) {
        int n = a.size();
        vector<ll> dp(n + 1, inf);
        dp[0] = 0;
        vector<int> pos(k, -1);
        int x = 0;
        for(int i = 1; i <= n; i++) {
            x = (x + a[i - 1]) % k;
            dp[i] = dp[i - 1] + a[i - 1];
            if(pos[x] != -1) {
                dp[i] = min(dp[i], dp[pos[x] - 1]);
            }
            pos[x] = i;
        }
        return dp[n];
    }
};