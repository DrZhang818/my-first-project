#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

i64 dp[17 * 2 * 2 * 10 * 140 + 1];
int vis[17 * 2 * 2 * 10 * 140 + 1];
int numL[17], numR[17];

int getId(int a, int b, int c, int d, int e) {
    return a * 2 * 2 * 10 * 140 + b * 2 * 10 * 140 + c * 10 * 140 + d * 140 + e;
}

bool check(int x) {
    bool inc = true, dec = true;
    int las = -1;
    while(x) {
        int p = x % 10;
        x /= 10;
        if(las != -1) {
            if(p >= las) inc = false;
            if(p <= las) dec = false;
        }
        las = p;
    }
    return inc || dec;
}

auto dfs(int cnt, int inc, int dec, int las, int sum, bool limL, bool limR) -> i64 {
    if(cnt == 0) {
        return inc || dec || check(sum);
    }
    if(!limL && !limR) {
        int id = getId(cnt, inc, dec, las, sum);
        if(vis[id]) {
            return dp[id];
        }  
    }
    int lo = limL ? numL[cnt] : 0;
    int hi = limR ? numR[cnt] : 9;
    i64 res = 0;
    for(int i = lo; i <= hi; i++) {
        bool s = limL && i == lo;
        bool t = limR && i == hi;
        if(las == -1) {
            if(i == 0) {
                res += dfs(cnt - 1, inc, dec, -1, sum, s, t);
            } else {
                res += dfs(cnt - 1, inc, dec, i, sum + i, s, t);
            }
        } else {
            if(i > las) {
                res += dfs(cnt - 1, inc, 0, i, sum + i, s, t);
            } else if(i < las) {
                res += dfs(cnt - 1, 0, dec, i, sum + i, s, t);
            } else {
                res += dfs(cnt - 1, 0, 0, i, sum + i, s, t);
            }
        }
    }
    if(!limL && !limR) {
        int id = getId(cnt, inc, dec, las, sum);
        dp[id] = res;
        vis[id] = true;
    }
    return res;
};

auto work(i64 l, i64 r) {
    int cntL = 0, cntR = 0;
    for(int i = 0; i < 17; i++) {
        numL[i] = numR[i] = 0;
    }
    while(l) {
        numL[++cntL] = l % 10;
        l /= 10;
    }
    while(r) {
        numR[++cntR] = r % 10;
        r /= 10;
    }
    return dfs(cntR, 1, 1, -1, 0, 1, 1);
};

class Solution {
public:
    i64 countFancy(i64 l, i64 r) {
        return work(l, r);
    }
};