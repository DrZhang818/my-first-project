#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


vector<int> getLPS(string& s){
    int n = s.size();
    vector<int> lps(n, 0);
    int cur = 0;
    for(int i = 1; i < n; i++){
        while(cur > 0 && s[i] != s[cur]){
            cur = lps[cur - 1];
        }
        if(s[i] == s[cur]){
            cur++;
            lps[i] = cur;
        }
    }
    return lps;
}

vector<int> KMP(string& s, string& t){
    int n = s.size(), m = t.size();
    vector<int> lps = getLPS(t), pos;
    int j = 0;
    for(int i = 0; i < n; i++){
        while(j > 0 && s[i] != t[j]){
            j = lps[j - 1];
        }
        if(s[i] == t[j]){
            j++;
            if(j == m){
                pos.push_back(i - m + 1);
                j = lps[j - 1];
            }
        }
    }
    return pos;
}
class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        vector<string> ss;
        string cur;
        for(auto c : p) {
            if(c == '*') {
                if(cur != "") {
                    ss.emplace_back(cur);
                }
                cur = "";
            }
            else {
                cur += c;
            }
        }      
        if(ss.size() == 0) {
            return 0;
        }
        int size = ss.size();
        int n = s.size();
        int ans = 1000000;
        vector<int> pos = KMP(s, ss[0]);
        bool ok = false;
        for(int i = 0; i < pos.size(); i++) {
            int len = ss[0].size();
            int j = 1, cur = pos[i] + len;
            ok = true;
            int tmp = len;
            while(j != ss.size()) {
                auto it = s.find(ss[j], cur);
                if(it == string::npos) {
                    ok = false;
                    break;
                }
                tmp += (int)it - cur + 1 + ss[j].size();
                cur += it + ss[j].size();
                j++;
            }
            if(ok == false) {
                break;
            }
            ans = min(ans, tmp);
        }
        return ans == 1000000 ? -1 : ans;
    }
};