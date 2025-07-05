#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 1000000000;
class Solution {
public:
    int maxProfit(vector<int>& a) {
        int dp0 = 0, dp1 = -inf;
        for(int i = 0; i < a.size(); i++) {
            int ndp0 = max(dp0, dp1 + a[i]);
            int ndp1 = max(dp1, dp0 - a[i]);
            dp0 = ndp0, dp1 = ndp1;
        }
        return dp0;
    }
};