#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

bool vis[17] {};

i64 dp[17][10];

int numL[17], numR[17];

i64 dfs(int pos, int las, bool lead, bool limL, bool limR) {
    if(pos == 0) {
        return 1;
    }
    if(!lead && !limL && !limR && dp[pos][las] != -1) return dp[pos][las];
    i64 res = 0;
    int lo = limL ? numL[pos] : 0;
    int hi = limR ? numR[pos] : 9;

    for(int i = lo; i <= hi; i++) {
        if(lead && i == 0) {
            res += dfs(pos - 1, vis[pos] ? i : las, true, limL && i == lo, limR && i == hi);
        } else if(!vis[pos] || i >= las) {
            res += dfs(pos - 1, vis[pos] ? i : las, false, limL && i == lo, limR && i == hi);
        }         
    }

    if(!lead && !limL && !limR) {
        dp[pos][las] = res;
    }    

    return res;
}

class Solution {
public:
    i64 countGoodIntegersOnPath(i64 l, i64 r, string directions) {
        memset(dp, -1, sizeof dp);
        memset(vis, 0, sizeof vis);

        int x = 0, y = 0;
        vis[16] = true;
        for(char c : directions) {
            if(c == 'D') x += 1;
            else y += 1;
            vis[16 - (4 * x + y)] = true;
        } 

        for(int i = 0; i < 16; i++) {
            numL[i + 1] = l % 10;
            numR[i + 1] = r % 10;
            l /= 10;
            r /= 10;
        }

        return dfs(16, 0, true, true, true);
    }
};