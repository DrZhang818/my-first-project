#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll maximumMedianSum(vector<int>& a) {
        sort(a.begin(), a.end());  
        ll ans = 0;
        for(int l = 0, r = a.size() - 1; l < r; l++, r -= 2) {
            ans += a[r - 1];
        }
        return ans;
    }
};