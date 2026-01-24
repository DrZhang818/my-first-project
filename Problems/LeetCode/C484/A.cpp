#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int residuePrefixes(string s) {
        vector<int> cnt(26);
        int n = s.size();
        int ans = 0;
        for(int i = 0, j = 0; i < n; i++) {
            if(cnt[s[i] - 'a'] == 0) {
                j++;
            }
            cnt[s[i] - 'a']++;
            if(j == (i + 1) % 3) {
                ans++;
            }
        }
        return ans;
    }
};