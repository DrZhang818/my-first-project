#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 1000000000;
class Solution {
public:
    int maxProfit(vector<int>& a) {
        int n = a.size();
        int dp0 = -inf, dp1 = -inf, dp2 = 0;
        for(int i = 0; i < n; i++) {
            int n0 = max(dp0, dp2 - a[i]);
            int n1 = dp0 + a[i];
            int n2 = max(dp1, dp2);
            dp0 = n0, dp1 = n1, dp2 = n2;
        }
        return max(dp1, dp2);
    }
};