#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
public:
    int countArrangement(int n) {
        vector<int> memo(1 << n, -1);
        auto dfs = [&](this auto&& dfs, int msk, int i) -> int {
            if(i == n + 1) return 1;
            int &res = memo[msk];
            if(res != -1) return res;
            res = 0;
            for(int j = 0; j < n; j++) {
                if((msk & (1 << j)) == 0) {
                    if(i % (j + 1) == 0 || (j + 1) % i == 0) {
                        res += dfs(msk | (1 << j), i + 1);
                    }
                }
            }
            return res;
        };
        return dfs(0, 1);
    }
};
class Solution1 {
public:
    int countArrangement(int n) {
        vector<int> dp(1 << n);
        dp[(1 << n) - 1] = 1;
        for(int msk = (1 << n) - 2; msk >= 0; msk--){
            int i = __builtin_popcount(msk) + 1;
            for(int j = 0; j < n; j++) {
                if((msk & (1 << j)) == 0) {
                    if(i % (j + 1) == 0 || (j + 1) % i == 0) {
                        dp[msk] += dp[msk | (1 << j)];
                    }
                }
            }
        }
        return dp[0];
    }
};