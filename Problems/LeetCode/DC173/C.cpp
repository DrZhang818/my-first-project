#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
const int N = 100005;

class Solution {
public:
    int findMaxVal(int n, vector<vector<int>>& a, vector<int>& d) {
        int ans = 0;
        vector<int> mx(n, inf);
        for(int i = 0; i < a.size(); i++) {
            int p = a[i][0], v = a[i][1];
            mx[p] = min(mx[p], v);
        }
        for(int i = n - 2; i >= 0; i--) {
            mx[i] = min(mx[i], mx[i + 1] + d[i]);
        }
        int cur = 0;
        for(int i = 1; i < n; i++) {
            cur += d[i - 1];
            cur = min(cur, mx[i]);
            ans = max(ans, cur);
        }
        return ans;
    }
};