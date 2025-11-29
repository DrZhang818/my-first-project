#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int minimumFlips(int n) {
        string s;
        while(n) {
            s += '0' + (n & 1);
            n >>= 1;
        }
        int ans = 0;
        int m = s.size();
        for(int i = 0; i < m / 2; i++) {
            if(s[i] != s[m - 1 - i]) {
                ans += 2;
            }
        }
        return ans;
    }
};