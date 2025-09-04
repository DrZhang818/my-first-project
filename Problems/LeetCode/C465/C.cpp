#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll maxProduct(vector<int>& a) {
        int mx = *max_element(a.begin(), a.end());
        int w = bit_width((unsigned int)mx);
        vector<int> dp(1 << w);
        for(int x : a) {
            dp[x] = x;
        }

        for(int i = 0; i < w; i++) {
            for(int s = 0; s < 1 << w; s++) {
                s |= 1 << i;
                dp[s] = max(dp[s], dp[s ^ (1 << i)]);
            }
        }

        ll ans = 0;
        for(int x : a) {
            ans = max(ans, 1LL * x * dp[((1 << w) - 1) ^ x]);
        }
        return ans;
    }
};