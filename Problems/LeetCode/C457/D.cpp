#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        if(sx == tx && sy == ty) return 0;
        if(sx > tx || sy > ty) return -1;
        if(sx == 0 && sy == 0) return -1;
        map<PII,int> mp;
        auto dfs = [&](this auto &&self, int x, int y) -> int {
            if(x == sx && y == sy) return 0;
            if(x < sx || y < sy) return inf;
            if(mp.contains({x,y})) return mp[{x, y}];
            int res = inf;
            if(2 * x >= y) {
                res = min(res, self(x, y - x) + 1);
            } else if(y % 2 == 0) {
                res = min(res, self(x, y >> 1) + 1);
            }
            if(2 * y >= x) {
                res = min(res, self(x - y, y) + 1);
            } else if(x % 2 == 0) {
                res = min(res, self(x >> 1, y) + 1);
            }

            return mp[{x, y}] = res;
        };
        int ans = dfs(tx, ty);
        return ans == inf ? -1 : ans;
    }
};