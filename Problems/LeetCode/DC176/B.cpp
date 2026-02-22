#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int prefixConnected(vector<string>& a, int k) {
        unordered_map<string,int> mp;
        int ans = 0;
        for(const string& s : a) {
            if(s.size() < k) continue;
            string t = s.substr(0, k);
            if(++mp[t] == 2) {
                ans++;
            }
        }      
        return ans;
    }
};