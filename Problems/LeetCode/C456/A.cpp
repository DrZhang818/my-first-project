#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    vector<string> partitionString(string s) {
        vector<string> ans;
        string cur;
        unordered_set<string> st;
        for(char c : s) {
            if(!cur.empty() && !st.count(cur)) {
                ans.push_back(cur);
                st.insert(cur);
                cur.clear();
            }
            cur += c;
        }    
        if(!cur.empty() && !st.count(cur)) ans.push_back(cur);
        return ans;
    }
};