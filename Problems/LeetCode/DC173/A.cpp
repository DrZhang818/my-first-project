#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    string reversePrefix(string s, int k) {
        for(int i = 0; i < k / 2; i++) {
            swap(s[i], s[k - 1 - i]);
        }
        return s;
    }
};