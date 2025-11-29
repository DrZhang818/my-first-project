#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        string ans = "";
        int n = s.size();
        array<int,26> cnt;
        for(int i = 0; i < n; i++) {
            cnt[s[i] - 'a']++;
        }
        auto dfs = [&](this auto &&self, int i) -> bool {
            if(i == n) return false;
            char c = target[i];
            if(cnt[c - 'a']) {
                ans += c;
                cnt[c - 'a']--;    
                if(self(i + 1)) {
                    return true;
                }
                ans.pop_back();
                cnt[c - 'a']++;
            }
            for(int j = c - 'a' + 1; j < 26; j++) {
                if(cnt[j]) {
                    ans += j + 'a';
                    cnt[j]--;
                    for(int k = 0; k < 26; k++) {
                        if(cnt[k]) {
                            ans += string(cnt[k], k + 'a');
                        }
                    }
                    return true;
                }
            }
            return false;
        };  
        dfs(0);
        return ans;
    }
};