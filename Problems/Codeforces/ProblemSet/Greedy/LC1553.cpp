#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 2000000000;

map<int,int> dp;
class Solution {
public:
    int minDays(int n) {
        auto dfs = [&](this auto &&self, int x) -> int {
            if(x == 0) {
                return 0;
            }
            if(dp.contains(x)) {
                return dp[x];
            }
            int res = min(x % 2 + 1 + self(x / 2), x % 3 + 1 + self(x / 3));
            return dp[x] = res;
        };
        return dfs(n);
    }
};
