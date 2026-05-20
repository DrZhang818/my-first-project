#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;
constexpr db pi = 3.141592653589793;

class Solution {
public:
    vector<db> internalAngles(vector<int>& sides) {
        int a, b, c;
        tie(a, b, c) = tuple {sides[0], sides[1], sides[2]};
        if(a + b <= c || b + c <= a || a + c <= b) {
            return {};
        }
        vector<db> ans;
        ans.push_back(acos((db)(a * a + b * b - c * c) / (2 * a * b)) * 180 / pi);
        ans.push_back(acos((db)(c * c + b * b - a * a) / (2 * c * b)) * 180 / pi);
        ans.push_back(acos((db)(a * a + c * c - b * b) / (2 * a * c)) * 180 / pi);
        sort(ans.begin(), ans.end());
        return ans;
    }
};