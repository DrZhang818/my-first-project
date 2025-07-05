#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int cal(string &s, string &t) {
        int res = 0;
        for(int i = 0, j = 0; i < s.size() && j < t.size(); i++,j++) {
            if(s[i] == t[j]) {
                res++;
            } else {
                break;
            }
        }
        return res;
    }
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        if(n == 1) {
            return {0};
        }
        vector<int> len(n - 1);
        for(int i = 0; i < n - 1; i++) {
            len[i] = cal(words[i], words[i + 1]);
        }
        vector<int> pre(n - 1), suf(n - 1);
        pre[0] = len[0], suf[n - 2] = len[n - 2];
        for(int i = 1; i < n - 1; i++) {
            pre[i] = max(pre[i - 1], len[i]);
        }
        for(int i = n - 3; i >= 0; i--) {
            suf[i] = max(suf[i + 1], len[i]);
        }
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            if(i - 2 >= 0) ans[i] = pre[i - 2];
            if(i + 1 < n - 1) ans[i] = max(ans[i], suf[i + 1]);
            if(i - 1 >= 0 && i + 1 < n) ans[i] = max(ans[i], cal(words[i - 1], words[i + 1]));
        }
        return ans;
    }
};