#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/unique-substrings-in-wraparound-string/
/*
	

*/
class Solution {
public:
    int findSubstringInWraproundString(string s) {
        vector<int> dp(26);
        int n = s.size();
        for(int i = 0, len = 1; i < n; i++){
            int c = s[i] - 'a';
            if(i == 0) {
                dp[c] = len;
                continue;
            }
            int pre = s[i - 1] - 'a';
            if(c == (pre + 1) % 26){
                len++;
            }else{
                len = 1;
            }
            dp[c] = max(dp[c], len);
        }
        ll ans = 0;
        for(int i = 0; i < 26; i++){
            ans += dp[i];
        }
        return ans;
    }
};