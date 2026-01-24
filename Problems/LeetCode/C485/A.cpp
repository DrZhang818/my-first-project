#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    string t = "aeiou";
    int vowelConsonantScore(string s) {
        int c0 = 0, c1 = 0;
        for(char c : s) {
            if(t.find(c) != string::npos) {
                c0++;
            } else if(isalpha(c)) {
                c1++;
            }
        }
        if(c1 == 0) return 0;
        return c0 / c1;
    }
};