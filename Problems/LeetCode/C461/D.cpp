#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

class Solution {
public:
    ll maxSumTrionic(vector<int>& a) {
        int n = a.size();
        a.insert(a.begin(), 0);
        array<ll,3> dp({-inf,-inf,-inf});
        ll ans = -inf;
        for(int i = 1; i < n; i++) {
            array<ll,3> ndp({-inf,-inf,-inf});
            if(a[i + 1] > a[i]) {
                ndp[0] = max(dp[0] + a[i + 1], (ll)a[i] + a[i + 1]);
                ndp[2] = max(dp[2] + a[i + 1], dp[1] + a[i + 1]);
            }
            if(a[i + 1] < a[i]) {
                ndp[1] = max(dp[1] + a[i + 1], dp[0] + a[i + 1]);
            }
            swap(dp, ndp);
            ans = max(ans, dp[2]);
        }
        return ans;
    }
};