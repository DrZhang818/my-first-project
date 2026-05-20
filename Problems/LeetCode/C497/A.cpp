#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

class Solution {
public:
    vector<int> findDegrees(vector<vector<int>>& a) {
        int n = a.size();
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                if(a[i][j]) {
                    ans[i]++;
                    ans[j]++;
                }
            }
        }
        return ans;
    }
};