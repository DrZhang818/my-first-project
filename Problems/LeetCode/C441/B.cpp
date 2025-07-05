#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
class Solution {
public:
    vector<int> solveQueries(vector<int>& a, vector<int>& b) {
        int n = a.size(), q = b.size();
        vector<int> ans(q);
        map<int,set<int>> mp;
        for(int i = 0; i < n; i++) {
            mp[a[i]].insert(i);
        }
        for(int i = 0; i < q; i++) {
            int x = a[b[i]];
            auto &st = mp[x];
            auto it = st.lower_bound(b[i]);
            int cur = 1000000000;
            if(it != st.begin()) {
                cur = min(cur, i - *st.begin());
            }
            if(*it != *st.rbegin()) {
                cur = min(cur, *st.rbegin() - i);
            }
            it++;
            if(it != st.end()) {
                cur = min(cur, *it - i);
            }
            it--;
            if(it != st.begin()) {
                it--;
                cur = min(cur, i - *it);
            }
            
            ans[i] = cur;
        }
        return ans;
    }
};