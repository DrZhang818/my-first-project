#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
class Solution {
public:
    vector<int> minCosts(vector<int>& a) {
        int n = a.size();
        vector<int> ans(n);
        int mn = 1000000000;
        for(int i = 0; i < n; i++) {
            mn = min(mn, a[i]);
            ans[i] = mn;
        }
        return ans;
    }
};