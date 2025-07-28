#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    string processStr(string s) {
        string t;
        for(char c : s) {
            if(isalpha(c)) {
                t += c;
            } else if(c == '#') {
                t += t;
            } else if(c == '*') {
                t.pop_back();
            } else {
                reverse(t.begin(), t.end());
            }
        }
        return t;        
    }
};