#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    string mapWordWeights(vector<string>& a, vector<int>& w) {
        string ans;
        for(const string& s : a) {
            int cur = 0;
            for(char c : s) {
                cur += w[c - 'a'];
            }
            cur %= 26;
            cur = 25 - cur;

            ans += char('a' + cur);
        }
        return ans;
    }
};