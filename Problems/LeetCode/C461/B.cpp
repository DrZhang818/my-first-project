#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int maxBalancedShipments(vector<int>& a) {
        int ans = 0, mx = -inf;
        for(int x : a) {
            if(x < mx) {
                ans++;
                mx = -inf;
            } else {
                mx = max(mx, x);
            }
        }
        return ans;
    }
};