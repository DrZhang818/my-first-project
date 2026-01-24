#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    string lexSmallestAfterDeletion(string s) {
        vector<int> cnt(26);
        for(char c : s) {
            cnt[c - 'a']++;            
        }
        stack<char> stk;
        for(char c : s) {
            while(!stk.empty() && stk.top() > c && cnt[stk.top() - 'a'] > 1) {
                cnt[stk.top() - 'a']--;
                stk.pop();
            }
            stk.push(c);
        }
        while(!stk.empty() && cnt[stk.top() - 'a'] > 1) {
            cnt[stk.top() - 'a']--;
            stk.pop();
        }
        string ans(stk.size(), ' ');
        int p = stk.size() - 1;
        while(!stk.empty()) {
            ans[p--] = stk.top();
            stk.pop();
        }
        return ans;
    }
};