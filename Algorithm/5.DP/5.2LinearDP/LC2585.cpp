#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
class Solution {
public:
    int waysToReachTarget(int k, vector<vector<int>>& T) {
        vector<int> dp(k + 1);
        dp[0] = 1;
        for(int i = 0; i < T.size(); i++) {
            for(int j = k; j >= 0; j--) {
                for(int s = 1; s <= T[i][0]; s++) {
                    if(j >= s * T[i][1]) {
                        add(dp[j], dp[j - s * T[i][1]]);
                    } else {
                        break;
                    }
                }
            }
        }
        return dp[k];
    }
};