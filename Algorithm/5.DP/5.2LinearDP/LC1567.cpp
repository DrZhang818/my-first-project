#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
class Solution {
public:
    int getMaxLen(vector<int>& a) {
        int n = a.size();
        int dp1 = 0, dp2 = 0;
        int ans = 0;
        for(int x : a) {
            int n1, n2;
            if(x == 0) {
                n1 = 0;
                n2 = 0;
            } else if(x > 0) {
                n1 = dp1 + 1;
                n2 = dp2 + 1;
            } else {
                n1 = dp2 + 1;
                n2 = dp1 + 1;
            }
            dp1 = n1, dp2 = n2;
            ans = max(ans, dp1);
        }   
        return ans;
    }
};