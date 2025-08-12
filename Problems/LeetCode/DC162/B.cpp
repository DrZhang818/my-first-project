#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minRemoval(vector<int>& a, int k) {
        int r = 0, n = a.size();
        int ans = inf;
        sort(a.begin(), a.end());
        for(int l = 0; l < n; l++) {
            while(r < n && a[r] <= 1LL * a[l] * k) {
                r++;
            }
            ans = min(ans, l + n - r);
        }
        return ans;
    }
};