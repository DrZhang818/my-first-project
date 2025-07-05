#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


class Solution {
public:
    typedef long long ll;
    ll minCost(int n, vector<vector<int>>& cost) {
        ll ans = 0;
        // ll dp[4][4][n] = {0};
        // for(int l = 0; l < n / 2 - 1; l++){
        //     int r = n - 1 - l;
        //     for(int i = 0; i < 3; i++){
        //         for(int j = 0; j < 3; j++){
        //             dp[i][j][l] = 
        //         }
        //     }
        // }
        vector<vector<vector<ll>>> memo(4, vector<vector<ll>>(4, vector<ll>(n, -1)));
        auto dfs = [&](auto &&dfs, int pre, int suf, int l) -> ll{
            if(l >= n / 2) return 0;
            ll &res = memo[pre + 1][suf + 1][l];
            if(res != -1) return res;
            res = LLONG_MAX;
            for(int i = 0; i < 3; i++){
                if(i == pre) continue;
                for(int j = 0; j < 3; j++){
                    if(j == i || j == suf) continue;
                    ll cur = cost[l][i] + cost[n - 1 - l][j];
                    cur += dfs(dfs, i, j, l + 1);
                    res = min(res, cur);
                }                
            }
            return res;
        };
        ans = dfs(dfs, -1, -1, 0);
        return ans;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    return 0;
}