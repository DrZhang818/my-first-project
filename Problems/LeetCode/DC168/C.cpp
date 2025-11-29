#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll minOperations(vector<int>& a, vector<int>& b) {
        int n = a.size(), d = inf;
        ll ans = 1;
        for(int i = 0; i < n; i++) {
            ans += abs(a[i] - b[i]);
            int mn = min(a[i], b[i]);
            int mx = max(a[i], b[i]);
            if(mn <= b[n] && b[n] <= mx) {
                d = 0;
            } else if(b[n] < mn) {
                d = min(d, mn - b[n]);
            } else {
                d = min(d, b[n] - mx);
            }
        }
        ans += d;
        return ans;
    }
};