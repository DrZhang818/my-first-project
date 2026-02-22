#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    string maximumXor(string s, string t) {
        int c0 = 0, c1 = 0;
        for(char c : t) {
            if(c == '0') {
                c0++;
            } else {
                c1++;
            }
        }
        int n = t.size();
        string ans(n, ' ');
        for(int i = 0; i < n; i++) {
            char c = s[i];
            if(c == '0') {
                if(c1) {
                    ans[i] = '1';
                    c1--;
                } else {
                    ans[i] = '0';
                    c0--;
                }
            } else {
                if(c0) {
                    ans[i] = '1';
                    c0--;
                } else {
                    ans[i] = '0';
                    c1--;
                }
            }
        }
        return ans;
    }
};