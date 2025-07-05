#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    string resultingString(string s) {
        stack<int> stk;
        string ans;
        for(int i = 0; i < s.size(); i++) {
            int x = s[i];
            if(!stk.empty() && (x == (stk.top() + 1) % 26 || x == (stk.top() + 25) % 26)) {
                stk.pop();
            } else {
                stk.push(x);
            }
        }
        while(!stk.empty()) {
            ans += stk.top();
            stk.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};