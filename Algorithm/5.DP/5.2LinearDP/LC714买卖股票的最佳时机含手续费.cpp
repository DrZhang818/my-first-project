#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 1000000000; 
class Solution {
public:
    int maxProfit(vector<int>& a, int k) {
        int n = a.size();
        int dp0 = 0, dp1 = -inf;
        for(int i = 0; i < n; i++) {
            int n0 = max(dp0, dp1 + a[i]);
            int n1 = max(dp0 - k - a[i], dp1);
            dp0 = n0, dp1 = n1;
        }
        return max(dp0, dp1);
    }
};