#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, d;
    friend bool operator < (const info &a, const info &b) {
        return a.x < b.x;
    }
};
class Solution {
public:
    int maxWalls(vector<int>& a, vector<int>& b, vector<int>& c) {
        int n = a.size(), m = b.size();
        vector<info> pos(n);
        for(int i = 0; i < n; i++) {
            pos[i] = {a[i], b[i]};
        }
        sort(pos.begin(), pos.end());
        sort(c.begin(), c.end());
        vector<array<int,2>> dp(n);
        for(int i = 0; i < n; i++) {
            int l = pos[i].x - pos[i].d, r = pos[i].x + pos[i].d;
            if(i != 0) l = max(l, pos[i - 1].x + 1);
            if(i != n - 1) r = min(r, pos[i + 1].x - 1);
            int L = lower_bound(c.begin(), c.end(), l) - c.begin();
            int M = lower_bound(c.begin(), c.end(), pos[i].x) - c.begin();
            int R = upper_bound(c.begin(), c.end(), r) - c.begin();
            int tag = 0;
            if(c[M] == pos[i].x) tag = 1;
            if(i == 0) {
                dp[i][0] = M - L + tag;
                dp[i][1] = R - M;
            } else {
                l = max(l, pos[i - 1].x + pos[i - 1].d + 1);
                int L2 = lower_bound(c.begin(), c.end(), l) - c.begin();
                dp[i][0] = dp[i - 1][0] + M - L + tag;
                dp[i][0] = max(dp[i][0], dp[i - 1][1] + M - L2 + tag);
                dp[i][1] = R - M;
            }
        }
        return max(dp[n - 1][0], dp[n - 1][1]);
    }
};