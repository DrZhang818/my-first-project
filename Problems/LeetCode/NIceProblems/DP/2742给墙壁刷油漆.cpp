#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 1000000000;
class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = cost.size();
        vector<int> dp(n + 1, inf);
        dp[0] = 0;
        for(int i = 0; i < n; i++){
            int x = time[i];
            for(int j = n; j >= x; j--){
                dp[j] = min(dp[j], dp[j - x]);
            }
        }
        return dp[n];
    }
};