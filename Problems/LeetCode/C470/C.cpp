#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    string removeSubstring(string s, int k) {
        stack<int> stk;
        for(char c : s) {
            if(stk.empty()) {
                if(c == '(') {
                    stk.push(1);
                } else {
                    stk.push(0);
                }
                continue;
            }
            int x = stk.top();
            if(x <= k) {
                if(c == '(') {
                    stk.push(min(k, x + 1));
                } else {
                    if(x == k) {
                        if(k == 1) {
                            stk.pop();
                        } else {
                            stk.push(k + 1);
                        }
                    } else {
                        stk.push(0);
                    }
                }
            } else {
                if(c == '(') {
                    stk.push(1);
                } else {
                    if(x == 2 * k - 1) {
                        for(int i = 0; i < 2 * k - 1; i++) {
                            stk.pop();
                        }
                    } else {
                        stk.push(x + 1);
                    }
                }
            }
        }
        vector<int> a;
        while(!stk.empty()) {
            a.push_back(stk.top());
            stk.pop();
        }
        reverse(a.begin(), a.end());
        string ans;
        for(int x : a) {
            if(1 <= x && x <= k) {
                ans += '(';
            } else {
                ans += ')';
            }
        }
        return ans;
    }
};