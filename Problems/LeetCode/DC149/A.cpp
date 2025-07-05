#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
public:
    string findValidPair(string s) {
        int cnt[10];
        for(int i = 0; i < s.size(); i++){
            int c = s[i] - '0';
            cnt[c]++;
        }      
        string ans;
        for(int i = 0; i < s.size() - 1; i++){
            if(s[i] != s[i + 1] && cnt[s[i] - '0'] == s[i] - '0' && cnt[s[i + 1] - '0'] == s[i + 1] - '0'){
                ans += s[i];
                ans += s[i + 1];
            }
        }
        return ans;
    }
};