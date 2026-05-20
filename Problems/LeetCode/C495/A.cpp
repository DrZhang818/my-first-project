#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

class Solution {
public:
    int firstMatchingIndex(string s) {
        int n = s.size();
        for(int i = 0; i < n; i++) {
            if(s[i] == s[n - 1 - i]) {
                return i;
            }
        }
        return -1;
    }
};