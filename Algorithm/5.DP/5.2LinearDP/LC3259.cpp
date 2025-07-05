#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
class Solution {
public:
    ll maxEnergyBoost(vector<int>& A, vector<int>& B) {
        ll dp0 = 0, dp1 = 0;
        int n = A.size();
        for(int i = 0; i < n; i++) {
            ll n0 = max(dp0 + A[i], dp1);
            ll n1 = max(dp1 + B[i], dp0);
            dp0 = n0, dp1 = n1;
        }
        return max(dp0, dp1);
    }
};