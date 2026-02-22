#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int scoreDifference(vector<int>& a) {
        int ans = 0;
        for(int i = 0, s = 0; i < a.size(); i++) {
            if(a[i] & 1) {
                s ^= 1;
            }
            if(i % 6 == 5) {
                s ^= 1;
            }
            if(s == 0) {
                ans += a[i];
            } else {
                ans -= a[i];
            }
        }
        return ans;
    }
};