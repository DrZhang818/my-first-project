#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minZeroArray(vector<int>& a, vector<vector<int>>& Q) {
        int n = a.size();
        int c0 = count(a.begin(), a.end(), 0);
        if(c0 == n) return 0;
        vector<bitset<1005>> dp(n);
        for(int i = 0; i < n; i++) {
            dp[i].set(0);
        }
        for(int k = 0; k < Q.size(); k++) {
            int l = Q[k][0], r = Q[k][1], v = Q[k][2];
            for(int i = l; i <= r; i++) {
                dp[i] |= dp[i] << v;
            }
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                if(dp[i][a[i]]) {
                    cnt++;
                }
            }
            if(cnt == n) {
                return k + 1;
            }
        }
        return -1;
    }
};