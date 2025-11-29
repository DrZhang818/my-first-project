#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = ll(1E15);

class Solution {
public:
    ll maximumScore(vector<int>& a, int k) {
        int n = a.size();
        vector<int> na(n + 1);
        int p = max_element(a.begin(), a.end()) - a.begin();
        int j = 1;
        for(int i = p; i < n; i++) {
            na[j++] = a[i];
        }
        for(int i = 0; i < p; i++) {
            na[j++] = a[i];
        }
        swap(a, na);
        auto work = [&]() -> ll {
            vector<ll> dp(k + 1);
            vector<ll> mn(k + 1, -inf), mx(k + 1, -inf);
            mn[0] = -a[1];
            mx[0] = a[1];
            for(int i = 2; i <= n; i++) {
                for(int j = 0; j <= k; j++) {
                    if(0 <= j && j < k) {
                        mn[j] = max(mn[j], dp[j] - a[i]);
                        mx[j] = max(mx[j], dp[j] + a[i]);
                    }
                    if(1 <= j && j <= k) {
                        dp[j] = max({dp[j], mx[j - 1] - a[i], mn[j - 1] + a[i]});
                    }
                }
            }
            ll ans = *max_element(dp.begin() + 1, dp.end());
            return ans;
        };
        ll ans = work();
        rotate(a.begin() + 1, a.begin() + 2, a.end());
        ans = max(ans, work());
        return ans;
    }
};