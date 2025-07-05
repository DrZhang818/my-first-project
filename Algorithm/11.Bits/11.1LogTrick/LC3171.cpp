#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int minimumDifference(vector<int>& a, int k) {
        int ans = inf, n = a.size();
        for(int r = 0; r < n; r++) {
            for(int l = r - 1; l >= 0 && (a[l] | a[r]) != a[l]; l--) {
                a[l] |= a[r];
                ans = min(ans, abs(a[l] - k));
            }
        }
        return ans;
    }
};