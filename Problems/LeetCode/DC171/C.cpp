#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    long long maxPoints(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        sort(p.begin(), p.end(), 
            [&](auto x, auto y) {
                return a[x] - b[x] > a[y] - b[y];
            });
        ll ans = 0;
        for(int x = 0; x < n; x++) {
            int i = p[x];
            if(x < k) {
                ans += a[i];
            } else {
                ans += max(a[i], b[i]);
            }
        }
        return ans;
    }
};