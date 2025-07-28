#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    struct info {
        string s;
        int id;
        friend bool operator < (const info &a, const info &b) {
            if(a.id != b.id) return a.id < b.id;
            return a.s < b.s;
        }
    };
    vector<string> validateCoupons(vector<string>& a, vector<string>& b, vector<bool>& tag) {
        int n = a.size();
        map<string,int> mp;
        mp["electronics"] = 1;
        mp["grocery"] = 2;
        mp["pharmacy"] = 3;
        mp["restaurant"] = 4;
        vector<info> t;
        for(int i = 0; i < n; i++) {
            if(a[i].empty() || !tag[i] || !mp[b[i]])  continue;
            bool ok = true;
            for(char c : a[i]) {
                if(!isalnum(c) && c != '_') {
                    ok = false;
                    break;
                }
            }
            if(!ok) continue;
            t.emplace_back(a[i], mp[b[i]]);
        }
        sort(t.begin(), t.end());
        vector<string> ans;
        for(auto &[s, _] : t) {
            ans.push_back(s);
        }
        return ans;
    }
};