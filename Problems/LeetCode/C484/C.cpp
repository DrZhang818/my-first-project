#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    ll countPairs(vector<string>& ss) {
        map<string,int> mp;
        ll ans = 0;
        for(string &s : ss) {
            int d = s[0] - 'a';
            for(int i = 0; i < s.size(); i++) {
                s[i] -= d;
                if(s[i] < 'a') {
                    s[i] += 26;
                }
            }
            ans += mp[s];
            mp[s]++;
        }
        return ans;
    }
};